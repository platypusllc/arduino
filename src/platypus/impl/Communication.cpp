#include "Communication.h"
#include "Platypus.h"
#include "platypus/Board.h"
#include "external/jsmn.h"

#include <algorithm>

// Maximum number of JSON tokens.
constexpr size_t NUM_JSON_TOKENS = 64;

/** Send status information about this controller. */
void sendHeader(Stream &stream)
{
  stream.print("{adk: {");
  stream.print("\"company_name\": \"");
  stream.print(platypus::board::ADK_COMPANY_NAME);
  stream.print("\", ");
  stream.print("\"url\": \"");
  stream.print(platypus::board::ADK_URL);
  stream.print("\", ");
  stream.print("\"accessory_name\": \"");
  stream.print(platypus::board::ADK_ACCESSORY_NAME);
  stream.print("\", ");
  stream.print("\"version_number\": \"");
  stream.println(platypus::board::ADK_VERSION_NUMBER);
  stream.print("\"}}");
}

/**
 * Returns a JSON error message to the connected USB device and the
 * serial debugging console.
 */
void reportError(Stream &stream, const char *error_message, const char *buffer)
{
  stream.print("{\"error\":\"");
  stream.print(error_message);
  stream.print("\",");
  stream.print("\"args\":\"");
  stream.print(buffer);
  stream.print("\"}");
  stream.flush();
}

/**
 * Constructs a JSON error message related to the parsing of a JSON string.
 */
void reportJsonError(Stream &stream, jsmnerr_t error, const char* buffer)
{
  char *errorMessage;
  
  // Fill in the appropriate JSON error description.
  switch(error) {
    case JSMN_SUCCESS:
      // If we were successful, there is nothing to report.
      return;
    case JSMN_ERROR_NOMEM:
      errorMessage = "Insufficient memory.";
      break;
    case JSMN_ERROR_INVAL:
      errorMessage = "Invalid JSON string.";
      break;
    case JSMN_ERROR_PART:
      errorMessage = "Incomplete JSON string.";
      break;
    default:
      errorMessage = "Unknown JSON error.";
      break;
  }

  // Send appropriate error message
  reportError(stream, errorMessage, buffer);
}

/**
 * Copies a JSON string token into a provided char* buffer.
 */
void jsonString(const jsmntok_t &token,
                const char *jsonStr, char *outputStr, size_t outputLen)
{
  size_t len = std::min(size_t(token.end - token.start), outputLen - 1);
  strncpy(outputStr, &jsonStr[token.start], len);
  outputStr[len] = '\0';
}

/**
 * Handler to respond to incoming JSON commands and dispatch them to
 * configurable hardware components.
 */
void handleCommand(platypus::Controller &controller, const char *buffer)
{
  jsmn_parser jsonParser;
  jsmnerr_t jsonResult;
  jsmntok_t jsonTokens[NUM_JSON_TOKENS];
  Stream &stream = controller.stream();

  // Initialize the JSON parser.
  jsmn_init(&jsonParser);
  
  // Parse command as JSON string.
  jsonResult = jsmn_parse(&jsonParser, buffer, jsonTokens, NUM_JSON_TOKENS);
  
  // Check for valid result, report error on failure.
  if (jsonResult != JSMN_SUCCESS)
  {
    reportJsonError(stream, jsonResult, buffer);
    return;
  }
  
  // Get the first token and make sure it is a JSON object.
  jsmntok_t *token = jsonTokens;
  if (token->type != JSMN_OBJECT) 
  {
    reportError(stream, "Commands must be JSON objects.", buffer);
    return;
  }
  
  // There should always be an even number of key-value pairs
  if (token->size & 1)
  {
    reportError(stream, "Command entries must be key-value pairs.", buffer);
    return;      
  }
  
  // Read each field of the JSON object and act accordingly.
  size_t num_entries = token->size / 2;
  for (size_t entry_idx = 0; entry_idx < num_entries; entry_idx++)
  {
    // Get the name field for this entry.
    token++;
    char entry_name[64];
    if (token->type != JSMN_STRING)
    {
      reportError(stream, "Expected name field for entry.", buffer);
      return;
    }
    jsonString(*token, buffer, entry_name, 64);
    
    // Attempt to decode the configurable object for this entry.
    platypus::Configurable *entry_object;
    
    // If it is a motor, it must take the form 'm1'.
    if (entry_name[0] == 'd')
    {
      size_t driveIdx = entry_name[1] - '0';
      if (driveIdx >= platypus::board::NUM_DRIVE_PORTS || entry_name[2] != '\0')
      {
        reportError(stream, "Invalid drive module index.", buffer);
        return;
      }
      entry_object = controller.driveModules_[driveIdx];
    }

    // If it is a motor, it must take the form 's1'.
    else if (entry_name[0] == 'm')
    {
      size_t multiIdx = entry_name[1] - '0';
      if (multiIdx >= platypus::board::NUM_MULTI_PORTS || entry_name[2] != '\0')
      {
        reportError(stream, "Invalid multi module index.", buffer);
        return;
      }
      entry_object = controller.multiModules_[multiIdx];
    }

    // Report parse error if unable to identify this entry.
    else {
      reportError(stream, "Unknown command entry.", buffer);
      return;
    }
    
    // The following token should always be the entry object.
    token++;
    if (token->type != JSMN_OBJECT) {
      reportError(stream, "Command entries must be objects.", buffer);
      return;      
    }

    // There should always be an even number of key-value pairs
    if (token->size & 1) {
      reportError(stream, "Command parameters must be key-value pairs.", buffer);
      return;      
    }
    
    // Iterate through each parameter.
    size_t numParams = token->size / 2;
    for (size_t paramIdx = 0; paramIdx < numParams; paramIdx++)
    {
      // Get the name field for this parameter.
      token++;
      char paramName[64];
      if (token->type != JSMN_STRING)
      {
        reportError(stream, "Expected name field for parameter.", buffer);
        return;
      }
      jsonString(*token, buffer, paramName, 64);

      // Get the value field for this parameter.
      token++;
      char paramValue[64];
      jsonString(*token, buffer, paramValue, 64);

      // Pass this parameter to the entry object.
      if (!entry_object->set(paramName, paramValue)) {
        reportError(stream, "Invalid parameter set.", buffer);
        return;
      }
    }
  } 
}

void streamLoop(void *data)
{
  platypus::Controller &controller = static_cast<platypus::Controller*>data;

  // Keep track of how many reads we haven't made so far.
  unsigned long lastCommandTime = 0;
  
  // Number of bytes received from USB.
  uint32_t bytesRead = 0;
  
  while (true)
  {
    // Do USB bookkeeping.
    Usb.Task();
    
    // Report system as shutdown if not connected to USB.
    if (!controller.adk_.isReady())
    {
      // If not connected to USB, we are 'DISCONNECTED'.
      if (controller.systemStatus_ != SystemStatus.DISCONNECTED)
      {
        send("{\"state\": \"disconnected\"}");
        controller.systemStatus_ = SystemStatus.DISCONNECTED;
      }
      
      // Wait for USB connection again.
      yield();
      continue;
    } 
    else 
    {  
      // If connected to USB, we are now 'CONNECTED'!
      if (controller.systemStatus_ == DISCONNECTED)
      {
        send("{\"state\": \"disconnected\"}");
        console.println("{\"state\": \"connected\"}");
        controller.systemStatus_ = CONNECTED; 
      }
    }
          
    // Attempt to read command from USB.
    controller.adk_.read(&bytesRead, INPUT_BUFFER_SIZE,
                         (uint8_t*)controller.command_buffer_);
    unsigned long currentCommandTime = millis();
    if (bytesRead <= 0)
    {
      // If we haven't received a response in a long time, maybe 
      // we are 'CONNECTED' but the server is not running.
      if (currentCommandTime - lastCommandTime >= RESPONSE_TIMEOUT_MS)
      {
        if (controller.systemStatus_ == RUNNING)
        {
          console.println("{\"state\": \"connected\"}");
          controller.systemStatus_ = CONNECTED; 
        }
      }
      
      // Wait for more USB data again.
      yield();
      continue;
    } 
    else 
    {
      // If we received a command, the server must be 'RUNNING'.
      if (controller.systemStatus_ == CONNECTED) 
      {
        console.println("{\"state\": \"running\"}");
        controller.systemStatus_ = RUNNING; 
      }
      
      // Update the timestamp of last received command.
      lastCommandTime = currentCommandTime;
    }
    
    // Properly null-terminate the buffer.
    controller.commandBuffer_[bytesRead] = '\0';
    
    // Copy incoming message to debug console.
    console.print("{\"cmd\": \"");
    console.print(controller.commandBuffer_);
    console.println("\"}");
      
    // Attempt to parse command
    handleCommand(controller.commandBuffer_);
  }
}

void consoleLoop(void *data)
{
  Controller &controller = static_cast<Controller*>data;
  Stream &console = controller.console();

  // Index to last character in console buffer.
  size_t consoleBufferIdx = 0;
  
  while (true)
  {
    // Wait until characters are received.
    while (!console.available()) yield();

    // Put the new character into the buffer.
    // TODO: read in batches.
    char c = console.read();
    controller.consoleBuffer_[consoleBufferIdx++] = c;

    // If it is the end of a line, or we are out of space, parse the buffer.
    if (consoleBufferIdx >= INPUT_BUFFER_SIZE || c == '\n' || c == '\r')
    {
      // Properly null-terminate the buffer.
      controller.consoleBuffer_[consoleBufferIdx] = '\0';
      consoleBufferIdx = 0;
      
      // Echo incoming message on debug console.
      console.print("{\"cmd\": \"");
      console.print(controller.consoleBuffer_);
      console.println("\"}");
      
      // Attempt to parse command.
      handleCommand(controller.consoleBuffer);
    }
  }
}
