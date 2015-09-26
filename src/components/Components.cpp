#include "Components.h"

using namespace platypus;

#define WAIT_FOR_CONDITION(condition, timeout_ms) for (unsigned int j = 0; j < (timeout_ms) && !(condition); ++j) delay(1);

bool AnalogSensor::set(const String &param, const String &value)
{
  // Set analog scale.
  if (param == "scale")
  {
    scale(value.toFloat());
    return true;
  }
  // Set analog offset.
  else if (param == "offset")
  {
    offset(value.toFloat());
    return true;
  }
  // Return false for unknown command.
  else
  {
    return false;
  }
}

void AnalogSensor::scale(float scale)
{
  scale_ = scale;
}

float AnalogSensor::scale()
{
  return scale_;
}

void AnalogSensor::offset(float offset)
{
  offset = offset_;
}

float AnalogSensor::offset()
{
  return offset_;
}

const String &AnalogSensor::name() const
{
  return "analog";
}

void ServoSensor::begin(MultiPort &port)
{
  int pin = port.beginDigital(MultiPin::TX_N, true, false);
  servo_.attach(pin);
}

void ServoSensor::end()
{
  servo_.detach();
}

void ServoSensor::position(float position)
{
  if (position > 1.0) {
    position = 1.0;
  }
  if (position < -1.0) {
    position = -1.0;
  }
  position_ = position;

  float command = (position_ * 600) + 1500;
  servo_.writeMicroseconds(command);
}

float ServoSensor::position()
{
  return position_;
}

bool ServoSensor::set(const String &param, const String &value)
{
  // Set motor velocity.
  if (param == "p")
  {
    position(value.toFloat());
    return true;
  }
  // Return false for unknown command.
  else
  {
    return false;
  }
}

const String &ServoSensor::name() const
{
  return "servo";
}

void PoweredSensor::begin(MultiPort &port)
{
  port.powerOn();
}

const String &PoweredSensor::name() const
{
  return "powered";
}
