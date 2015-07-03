#include "Platypus.h"
#include <Arduino.h>

using platypus::Motor;

Motor::Motor(int channel)
  : enable_(board::MOTOR[channel].ENABLE), enabled_(false), velocity_(0)
{
  servo_.attach(board::MOTOR[channel].SERVO);
  pinMode(enable_, OUTPUT);
  digitalWrite(enable_, LOW);
}

Motor::~Motor()
{
  pinMode(enable_, INPUT);
  digitalWrite(enable_, LOW);
  servo_.detach();
}

void Motor::velocity(float velocity)
{
  if (velocity > 1.0) {
    velocity = 1.0;
  }
  if (velocity < -1.0) {
    velocity = -1.0;
  }
  velocity_ = velocity;

  float command = (velocity * 500) + 1500;
  servo_.writeMicroseconds(command);
}

float Motor::velocity()
{
  return velocity_;
}

void Motor::enable(bool enabled)
{
  enabled_ = enabled;
  digitalWrite(enable_, enabled_);

  if (!enabled_)
  {
    velocity(0.0);
  }
}

bool Motor::enabled()
{
  return enabled_;
}

void Motor::enable()
{
  enable(true);
}

void Motor::disable()
{
  enable(false);
}

float Motor::current()
{
  // TODO: fill me in.
  return 0.0;
}

bool Motor::set(char *param, char *value)
{
  // Set motor velocity.
  if (!strncmp("v", param, 2))
  {
    float v = atof(value);
    velocity(v);
    return true;
  }
  // Return false for unknown command.
  else
  {
    return false;
  }
}

void Motor::loop()
{
  // Do nothing.
}

void Motor::onLoop_(void *data)
{ 
  // Resolve self-reference and call member function.
  Motor *self = (Motor*)data;
  self->loop();
}
