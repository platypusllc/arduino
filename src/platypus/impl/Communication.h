#ifndef PLATYPUS_COMMUNICATION_H
#define PLATYPUS_COMMUNICATION_H

#include <Arduino.h>
#include <adk.h>

namespace platypus
{
namespace impl
{

class Controller;

void sendHeader(Stream &stream);
void handleCommand(Controller &controller, const char *buffer);
void adkStreamLoop(void *data);
void serialStreamLoop(void *data);

} // impl
} // platypus

#endif // PLATYPUS_COMMUNICATION_H
