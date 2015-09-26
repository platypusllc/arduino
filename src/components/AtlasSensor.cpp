#include "AtlasSensor.h"

using namespace platypus;

void AtlasSensor::begin(MultiPort &port)
{
  // Start up serial port.
  Stream *serial = port.beginSerial(38400, SerialMode::RS232);

  // Tell sensor to start transmitting.
  serial->print("C\r");
}

const String &AtlasSensor::name() const
{
  return "atlas";
}

void AtlasSensor::loop()
{
  /*
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
         "\"type\":\"%s\","
         "\"data\":\"%s\""
       "}"
      "}",
      channel_,
      name(),
      recv_buffer_
    );  
    send(output_str);

    memset(recv_buffer_, 0, recv_index_);   
    recv_index_ = 0;
  }
  */
}
