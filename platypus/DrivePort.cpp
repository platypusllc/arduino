#include "DrivePort.h"
#include "Board.h"
#include <Servo.h>

class DrivePortImpl
: public platypus::DrivePort
{
public:
    void begin(int port);
    void end();

private:
    bool _isPowered;
    float _command;
    Servo _servo;
    int _port;
};

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
    digitalWrite(MOTOR[_port], isPowered);
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
    digitalWrite(board.MOT_SENSE, HIGH);
    int result = analogRead();
    digitalWrite(board.MOT_SENSE, LOW);
    return (float)result / 3.3;
}

void DrivePortImpl::reset()
{
    this->powerOff();
    this->command(0);
}
