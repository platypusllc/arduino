#include "AtlasSensor.h"

using namespace platypus;

AtlasSensor::AtlasSensor(int channel)
: Sensor(channel), recv_index_(0)
{
  // Start up serial port.
  SERIAL_PORTS[channel]->begin(38400);
  
  // Tell the sensor to output continuously.
  SERIAL_PORTS[channel_]->print("C\r");
}

char* AtlasSensor::name()
{
  return "atlas";
}

void AtlasSensor::onSerial()
{
  char c = SERIAL_PORTS[channel_]->read();
  if (c != '\r' && c != '\n' && recv_index_ < DEFAULT_BUFFER_SIZE)
  {
    recv_buffer_[recv_index_] = c;
    ++recv_index_;
  }
  else if (recv_index_ > 0)
  { 
    recv_buffer_[recv_index_] = '\0';
    
    char output_str[DEFAULT_BUFFER_SIZE+3];
    snprintf(output_str, DEFAULT_BUFFER_SIZE,
      "{"
       "\"s%u\":{"
         "\"type\":\"atlas\","
         "\"data\":\"%s\""
       "}"
      "}",
      channel_,
      recv_buffer_
    );  
    send(output_str);

    memset(recv_buffer_, 0, recv_index_);   
    recv_index_ = 0;
  }
}
