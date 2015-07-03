#include "DrivePort.h"
#include "Board.h"
#include <Servo.h>

using platypus::impl::DrivePort;

DrivePort::DrivePort(int port)
: _isPowered(false)
, _command(0)
, _servo()
{
    _servo.attach(MOTOR[_port].SERVO);
}

DrivePort::~DrivePort()
{
    _servo.detach();
}

void DrivePort::command(float cmd)
{
    _servo.set(_command);
}

float DrivePort::command() const;
{
    return _command;
}

bool DrivePort::isPowered() const
{
    return _isPowered;
}

void DrivePort::power(bool isPowered)
{
    digitalWrite(platypus::board::MOTOR[_port], isPowered);
    _isPowered = isPowered;
}

void DrivePort::powerOn()
{
    this->power(true);
}

void DrivePort::powerOff()
{
    this->power(false);
}
        
float DrivePort::current()
{
    digitalWrite(platypus::board::MOT_SENSE, HIGH);
    int result = analogRead(platypus::board::MOTOR[_port].CURRENT);
    digitalWrite(platypus::board::MOT_SENSE, LOW);
    return (float)result / 3.3;
}

void DrivePort::reset()
{
    this->powerOff();
    this->command(0);
}
