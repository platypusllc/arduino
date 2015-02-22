#include "MultiPort.h"
#include "Board.h"

class MultiPortImpl
: public platypus::MultiPort
{
private:
    bool _isEnabled;
    int _pinUsageMask;
    int _port;
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

MultiPortImpl::begin()
{
    // TODO: fill this in.
}

MultiPortImpl::end()
{
    // TODO: fill this in.
}

MultiPortImpl::loop()
{
    // TODO: fill this in.
}