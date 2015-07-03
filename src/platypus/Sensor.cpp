#include "Platypus.h"
#include <Arduino.h>

using platypus::Sensor;

Sensor::Sensor(int channel) 
: channel_(channel)
{  
  // Disable RSxxx receiver
  pinMode(board::SENSOR[channel].RX_DISABLE, OUTPUT);
  digitalWrite(board::SENSOR[channel].RX_DISABLE, HIGH);

  // Disable RSxxx transmitter
  pinMode(board::SENSOR[channel].TX_ENABLE, OUTPUT);
  digitalWrite(board::SENSOR[channel].TX_ENABLE, LOW);

  // Disable RS485 termination resistor
  pinMode(board::SENSOR[channel].RS485_TE, OUTPUT);
  digitalWrite(board::SENSOR[channel].RS485_TE, LOW);

  // Select RS232 (deselect RS485)
  pinMode(board::SENSOR[channel].RS485_232, OUTPUT);
  digitalWrite(board::SENSOR[channel].RS485_232, LOW);

  // TODO: deconflict this!
  if (channel < 2)
  {
    // Disable half-duplex
    pinMode(board::HALF_DUPLEX01, OUTPUT);
    digitalWrite(board::HALF_DUPLEX01, LOW);
  } 
  else 
  {
    // Disable half-duplex
    pinMode(board::HALF_DUPLEX23, OUTPUT);
    digitalWrite(board::HALF_DUPLEX23, LOW);
  }
  
  // Disable loopback test
  pinMode(board::LOOPBACK, OUTPUT);
  digitalWrite(board::LOOPBACK, LOW);
  
  // Disable 12V output
  pinMode(board::SENSOR[channel].PWR_ENABLE, OUTPUT);
  digitalWrite(board::SENSOR[channel].PWR_ENABLE, LOW);
  
  // Register serial event handler
  SerialHandler_t handler = {Sensor::onSerial_, this}; 
  SERIAL_HANDLERS[channel] = handler;
}

Sensor::~Sensor()
{
  // TODO: fill me in
}

bool Sensor::set(char* param, char* value)
{
  return false;
}

void Sensor::onSerial() 
{
  // Default to doing nothing on serial events. 
}

void Sensor::onSerial_(void *data)
{
  // Resolve self-reference and call member function.
  Sensor *self = (Sensor*)data;
  self->onSerial();
}

void Sensor::loop()
{
  // Do nothing.
}

void Sensor::onLoop_(void *data)
{ 
  // Resolve self-reference and call member function.
  Sensor *self = (Sensor*)data;
  self->loop();
}