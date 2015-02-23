#include "MultiPort.h"
#include "Board.h"
#include <Servo.h>

MultiPortImpl::MultiPortImpl()
: _pinUsageMask(0)
{
    // TODO: fill this in.
}

MultiPortImpl::~MultiPortImpl()
{
    // TODO: fill this in.
}

float MultiPortImpl::current()
{
    digitalWrite(board.SEN_SENSE, HIGH);
    int result = analogRead(board.SENSOR[port].CURRENT);
    digitalWrite(board.SEN_SENSE, LOW);
    return (float)result / 3.3;
}

MultiPortImpl::reset()
{

}
