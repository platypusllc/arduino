#include "Communication.h"
#include "Board.h"

using namespace platypus::impl;

/** Send status information about this controller. */
void sendHeader(Stream &stream)
{
  stream.print("{");
  stream.print("\"company_name\": \"");
  stream.print(platypus::board::ADK_COMPANY_NAME);
  stream.print("\", ")
  stream.print("\"url\": \"");
  stream.print(platypus::board::ADK_URL);
  stream.print("\", ")
  stream.print("\"accessory_name\": \"");
  stream.print(platypus::board::ADK_ACCESSORY_NAME);
  stream.print("\", ")
  stream.print("\"version_number\": \"");
  stream.println(platypus::board::ADK_VERSION_NUMBER);
  stream.print("\"}")
}

/**
 * Wrapper for ADK send command that copies data to debug port.
 * Requires a null-terminated char* pointer.
 */
void send(char *str) 
{ 
  // Add newline termination
  // TODO: Make sure we don't buffer overflow
  size_t len = strlen(str);
  str[len++] = '\r';
  str[len++] = '\n';
  str[len] = '\0';
  
  // Write string to USB.
  if (adk.isReady()) adk.write(len, (uint8_t*)str);
  
  // Copy string to debugging console.
  Serial.print("-> ");
  Serial.print(str);
}

/**
 * Returns a JSON error message to the connected USB device and the
 * serial debugging console.
 */
void reportError(const char *error_message, const char *buffer)
{
  // Construct a JSON error message.
  snprintf(output_buffer, OUTPUT_BUFFER_SIZE, 
           "{"
           "\"error\": \"%s\","
           "\"args\": \"%s\""
           "}",
           error_message, buffer);
  send(output_buffer);
}

/**
 * Constructs a JSON error message related to the parsing of a JSON string.
 */
void reportJsonError(jsmnerr_t error, const char* buffer)
{
  char *error_message;
  
  // Fill in the appropriate JSON error description.
  switch(error) {
    case JSMN_SUCCESS:
      // If we were successful, there is nothing to report.
      return;
    case JSMN_ERROR_NOMEM:
      error_message = "Insufficient memory.";
      break;
    case JSMN_ERROR_INVAL:
      error_message = "Invalid JSON string.";
      break;
    case JSMN_ERROR_PART:
      error_message = "Incomplete JSON string.";
      break;
    default:
      error_message = "Unknown JSON error.";
      break;
  }

  // Send appropriate error message
  reportError(error_message, buffer);  
}

/**
 * Copies a JSON string token into a provided char* buffer.
 */
void jsonString(const jsmntok_t &token,
                const char *json_str, char *output_str, size_t output_len)
{
  size_t len = min(token.end - token.start, output_len - 1);
  strncpy(output_str, &json_str[token.start], len);
  output_str[len] = '\0';
}

/**
 * Handler to respond to incoming JSON commands and dispatch them to
 * configurable hardware components.
 */
void handleCommand(Controller &controller, const char *buffer)
{
  // JSON parser structure
  jsmn_parser json_parser;
  
  // JSON token buffer
  const size_t NUM_JSON_TOKENS = 64;
  jsmntok_t json_tokens[NUM_JSON_TOKENS];
  
  // Result of JSON parsing.
  jsmnerr_t json_result;

  // Initialize the JSON parser.
  jsmn_init(&json_parser);
  
  // Parse command as JSON string
  json_result = jsmn_parse(&json_parser, buffer, json_tokens, NUM_JSON_TOKENS);
  
  // Check for valid result, report error on failure.
  if (json_result != JSMN_SUCCESS)
  {
    reportJsonError(json_result, buffer);
    return;
  }
  
  // Get the first token and make sure it is a JSON object.
  jsmntok_t *token = json_tokens;
  if (token->type != JSMN_OBJECT) 
  {
    reportError("Commands must be JSON objects.", buffer);
    return;
  }
  
  // There should always be an even number of key-value pairs
  if (token->size & 1) {
    reportError("Command entries must be key-value pairs.", buffer);
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
      reportError("Expected name field for entry.", buffer);
      return;
    }
    json_string(*token, buffer, entry_name, 64);
    
    
    // Attempt to decode the configurable object for this entry.
    platypus::Configurable *entry_object;
    
    // If it is a motor, it must take the form 'm1'.
    if (entry_name[0] == 'm')
    {
      size_t motor_idx = entry_name[1] - '0';
      if (motor_idx >= board::NUM_MOTORS || entry_name[2] != '\0') 
      {
        reportError("Invalid motor index.", buffer);
        return;
      }
      entry_object = platypus::motors[motor_idx];
    }
    // If it is a motor, it must take the form 's1'.
    else if (entry_name[0] == 's')
    {
      size_t sensor_idx = entry_name[1] - '0';
      if (sensor_idx >= board::NUM_SENSORS || entry_name[2] != '\0') 
      {
        reportError("Invalid sensor index.", buffer);
        return;
      }
      entry_object = platypus::sensors[sensor_idx];
    }
    // Report parse error if unable to identify this entry.
    else {
      reportError("Unknown command entry.", buffer);
      return;
    }
    
    // The following token should always be the entry object.
    token++;
    if (token->type != JSMN_OBJECT) {
      reportError("Command entries must be objects.", buffer);
      return;      
    }

    // There should always be an even number of key-value pairs
    if (token->size & 1) {
      reportError("Command parameters must be key-value pairs.", buffer);
      return;      
    }
    
    // Iterate through each parameter.
    size_t num_params = token->size / 2;
    for (size_t param_idx = 0; param_idx < num_params; param_idx++)
    {
      // Get the name field for this parameter.
      token++;
      char param_name[64];
      if (token->type != JSMN_STRING)
      {
        reportError("Expected name field for parameter.", buffer);
        return;
      }
      
      json_string(*token, buffer, param_name, 64);

      // Get the value field for this parameter.
      token++;
      char param_value[64];
      json_string(*token, buffer, param_value, 64);

      // Pass this parameter to the entry object.
      if (!entry_object->set(param_name, param_value)) {
        reportError("Invalid parameter set.", buffer);
        return;
      }
    }
  } 
}

void commandLoop(void *data)
{
  Controller &controller = static_cast<Controller*>data;
  Stream &console = controller.console();

  // Keep track of how many reads we haven't made so far.
  unsigned long last_command_time = 0;
  
  // Number of bytes received from USB.
  uint32_t bytes_read = 0;
  
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
        console.println("STATE: DISCONNECTED");
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
        console.println("STATE: CONNECTED");
        controller.systemStatus_ = CONNECTED; 
      }
    }
          
    // Attempt to read command from USB.
    controller.adk_.read(&bytes_read, INPUT_BUFFER_SIZE,
                         (uint8_t*)controller.command_buffer_);
    unsigned long current_command_time = millis();
    if (bytes_read <= 0) 
    {
      // If we haven't received a response in a long time, maybe 
      // we are 'CONNECTED' but the server is not running.
      if (current_command_time - last_command_time >= RESPONSE_TIMEOUT_MS)
      {
        if (controller.systemStatus_ == RUNNING)
        {
          console.println("STATE: CONNECTED");
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
        console.println("STATE: RUNNING");
        controller.systemStatus_ = RUNNING; 
      }
      
      // Update the timestamp of last received command.
      last_command_time = current_command_time;
    }
    
    // Properly null-terminate the buffer.
    controller.command_buffer_[bytes_read] = '\0';
    
    // Copy incoming message to debug console.
    console.print("<- ");
    console.println(controller.command_buffer_);
      
    // Attempt to parse command
    handleCommand(controller.command_buffer_);
  }
}

void consoleLoop(void *data)
{
  Controller &controller = static_cast<Controller*>data;
  Stream &console = controller.console();

  // Index to last character in console buffer.
  size_t console_buffer_idx = 0;
  
  while (true)
  {
    // Wait until characters are received.
    while (!console.available()) yield();

    // Put the new character into the buffer.  
    char c = console.read();
    controller.console_buffer_[console_buffer_idx++] = c;

    // If it is the end of a line, or we are out of space, parse the buffer.
    if (console_buffer_idx >= INPUT_BUFFER_SIZE || c == '\n' || c == '\r') 
    {
      // Properly null-terminate the buffer.
      controller.console_buffer_[console_buffer_idx] = '\0';
      console_buffer_idx = 0;
      
      // Echo incoming message on debug console.
      console.print("## ");
      console.println(controller.console_buffer_);
      
      // Attempt to parse command.
      handleCommand(console_buffer); 
    }
  }
}