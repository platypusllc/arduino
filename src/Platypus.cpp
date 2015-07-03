#include "Platypus.h"

using namespace platypus;

// TODO: Correct default initialization of these sensors.
platypus::Motor *platypus::motors[board::NUM_MOTORS];
platypus::Sensor *platypus::sensors[board::NUM_SENSORS];

// TODO: Switch to using HardwareSerial.
USARTClass *platypus::SERIAL_PORTS[4] = {
  NULL,
  &Serial1,
  &Serial2,
  &Serial3,
};

SerialHandler_t platypus::SERIAL_HANDLERS[4] = {
  {NULL, NULL},
  {NULL, NULL},
  {NULL, NULL},
  {NULL, NULL}
};

void serialEvent1() 
{
  if (SERIAL_HANDLERS[1].handler != NULL) 
  {
    (*SERIAL_HANDLERS[1].handler)(SERIAL_HANDLERS[1].data);
  }
}

void serialEvent2() 
{
  if (SERIAL_HANDLERS[2].handler != NULL) 
  {
    (*SERIAL_HANDLERS[2].handler)(SERIAL_HANDLERS[2].data);
  }
}

void serialEvent3() 
{ 
  if (SERIAL_HANDLERS[3].handler != NULL) 
  {
    (*SERIAL_HANDLERS[3].handler)(SERIAL_HANDLERS[3].data);
  }
}

uint32_t platypus::swap(uint32_t bytes)
{
  return ((bytes << 24) & 0xFF000000)
         | ((bytes <<  8) & 0x00FF0000)
         | ((bytes >>  8) & 0x0000FF00)
         | ((bytes >> 24) & 0x000000FF);
}

/**
 * Cooperative task schedulers for Platypus motors and sensors.
 */
void platypusLoop_()
{
  // TODO: Currently, this runs loops in series, which is wrong.
  // TODO: Parallelize these cooperative loops.
  
  // Run each motor loop task once.
  for (int motorIdx = 0; motorIdx < board::NUM_MOTORS; ++motorIdx)
  {
    Motor *motor = platypus::motors[motorIdx];
    if (motor != NULL)
    {
      platypus::Motor::onLoop_(motor);
    }
  }

  // Run each sensor loop task once.  
  for (int sensorIdx = 0; sensorIdx < board::NUM_SENSORS; ++sensorIdx)
  {
    Sensor *sensor = platypus::sensors[sensorIdx];
    if (sensor != NULL) 
    {
      platypus::Sensor::onLoop_(sensor);
    }
  }
}

void platypus::init()
{
  Scheduler.startLoop(platypusLoop_);
}
