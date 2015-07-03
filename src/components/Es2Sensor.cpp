#include "Es2Sensor.h"

using namespace platypus;

Es2Sensor::Es2Sensor(int channel)
: Sensor(channel), recv_index_(0)
{
  // Start up serial port
  SERIAL_PORTS[channel]->begin(1200);
}

char* Es2Sensor::name()
{
  return "es2";
}

void Es2Sensor::loop()
{
  // Enable +12V output.
  pinMode(board::SENSOR[channel_].PWR_ENABLE, OUTPUT);
  digitalWrite(board::SENSOR[channel_].PWR_ENABLE, HIGH);
  
  // Read response from sensor.
  delay(250);
  
  // Turn off +12V output.
  pinMode(board::SENSOR[channel_].PWR_ENABLE, OUTPUT);
  digitalWrite(board::SENSOR[channel_].PWR_ENABLE, LOW);
  
  // Wait a while for next sensor reading.
  delay(1750);
}

void Es2Sensor::onSerial()
{
  // TODO: verify checksum.
  char c = SERIAL_PORTS[channel_]->read();
  if (c == '\0') { 
    return;
  } 
  else if (c != '\r' && c != '\n' && recv_index_ < DEFAULT_BUFFER_SIZE)
  {
    recv_buffer_[recv_index_] = c;
    ++recv_index_;
  }
  else if (recv_index_ > 0)
  { 
    recv_buffer_[recv_index_] = '\0';
    
    if (recv_index_ > 6) // Only send data strings
    {
      char output_str[DEFAULT_BUFFER_SIZE+3];
      snprintf(output_str, DEFAULT_BUFFER_SIZE,
        "{"
         "\"s%u\":{"
           "\"type\":\"es2\","
           "\"data\":\"%s\""
         "}"
        "}",
        channel_,
        recv_buffer_
      );
      send(output_str);
    }

    memset(recv_buffer_, 0, recv_index_);
    recv_index_ = 0;
  }
}