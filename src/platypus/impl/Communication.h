#ifndef PLATYPUS_COMMUNICATION_H
#define PLATYPUS_COMMUNICATION_H

#include <adk.h>
#include <Arduino.h>

namespace platypus
{
namespace impl
{

class Controller;

void sendHeader(Stream &stream);
void handleCommand(Controller &controller, const char *buffer);
void adkStreamLoop(void *data);
void serialStreamLoop(void *data);

// Time betweeen commands before we consider the Android
// server to be unresponsive.
static constexpr size_t RESPONSE_TIMEOUT_MS = 500;

// Maximum size of input JSON messages.
static constexpr size_t INPUT_BUFFER_SIZE = 512;

} // impl
} // platypus

#endif // PLATYPUS_COMMUNICATION_H
