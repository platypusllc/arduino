#include "DrivePort.h"
#include "Board.h"
#include <Servo.h>

DrivePortImpl::DrivePortImpl(int port)
: _isPowered(false)
, _command(0)
, _servo()
{
    _servo.attach(MOTOR[_port].SERVO);
}

DrivePortImpl::~DrivePortImpl()
{
    _servo.detach();
}

void DrivePortImpl::command(float cmd)
{
    _servo.set(_command);
}

float DrivePortImpl::command() const;
{
    return _command;
}

bool DrivePortImpl::isPowered() const
{
    return _isPowered;
}

void DrivePortImpl::power(bool isPowered)
{
    digitalWrite(platypus::board::MOTOR[_port], isPowered);
    _isPowered = isPowered;
}

void DrivePortImpl::powerOn()
{
    this->power(true);
}

void DrivePortImpl::powerOff()
{
    this->power(false);
}
        
float DrivePortImpl::current()
{
    digitalWrite(platypus::board::MOT_SENSE, HIGH);
    int result = analogRead(platypus::board::MOTOR[_port].CURRENT);
    digitalWrite(platypus::board::MOT_SENSE, LOW);
    return (float)result / 3.3;
}

void DrivePortImpl::reset()
{
    this->powerOff();
    this->command(0);
}
