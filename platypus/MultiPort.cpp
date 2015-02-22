#include "MultiPort.h"
#include "Board.h"

namespace Pin {
    // This pin enumeration follows the MultiCon connector numbering.
    enum {
        V5 = 1,
        RX_P = 2,
        RX_N = 3,
        V12 = 4,
        TX_P = 5,
        TX_N = 6,
        ANA = 7,
        GND = 8
    } Mask;
}

class MultiPortImpl
: public platypus::MultiPort
{
public:
    void begin(int port);
    void end();

private:
    bool _isEnabled;
    volatile uint8_t _pinUsageMask;
};


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
    int result = analogRead();
    digitalWrite(board.SEN_SENSE, LOW);
    return (float)result / 3.3;
}

MultiPortImpl::reset()
{

}
