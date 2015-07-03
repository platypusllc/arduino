#ifndef PLATYPUS_COMMUNICATION_H
#define PLATYPUS_COMMUNICATION_H

#include <Arduino.h>
#include <adk.h>

namespace platypus
{
namespace impl
{

void sendHeader(Stream &stream);

void commandLoop(void *data);
void consoleLoop(void *data);

}
}

#endif // PLATYPUS_COMMUNICATION_H