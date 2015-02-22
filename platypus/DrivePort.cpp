#include "DrivePort.h"
#include "Board.h"

class DrivePortImpl
: public platypus::DrivePort
{
private:
    bool _isEnabled;
    int _port;
};

DrivePortImpl::DrivePortImpl()
: _isEnabled(false)
{
    // TODO: fill this in.
}

DrivePortImpl::~DrivePortImpl()
{
    // TODO: fill this in.
}

DrivePortImpl::begin()
{
    // TODO: fill this in.
}

DrivePortImpl::end()
{
    // TODO: fill this in.
}

DrivePortImpl::loop()
{
    // TODO: fill this in.
}