#ifndef PLATYPUS_COMMUNICATION_H
#define PLATYPUS_COMMUNICATION_H

#include <Arduino.h>
#include <adk.h>

namespace platypus
{
namespace impl
{

void sendHeader(Stream &stream);
void streamLoop(void *data);

} // impl
} // platypus

#endif // PLATYPUS_COMMUNICATION_H
