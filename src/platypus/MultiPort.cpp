#include "MultiPort.h"
#include "Board.h"
#include <Servo.h>

using platypus::impl::MultiPort;

MultiPort::MultiPort()
: _pinUsageMask(0)
{
    // TODO: fill this in.
}

MultiPort::~MultiPort()
{
    // TODO: fill this in.
}

float MultiPort::current()
{
    digitalWrite(board.SEN_SENSE, HIGH);
    int result = analogRead(board.SENSOR[port].CURRENT);
    digitalWrite(board.SEN_SENSE, LOW);
    return (float)result / 3.3;
}

MultiPort::reset()
{

}
