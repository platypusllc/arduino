#include "Controller.h"
#include "Board.h"

class ControllerImpl
: public platypus::Controller 
{
public:
    ControllerImpl();

    setDrivePort(DrivePort &device);
    setDrivePorts(DrivePort device[]);

    setMultiPort(MultiPort &device);
    setMultiPorts(MultiPort device[]);

    Led& led() const;
    float battery() const;
    Stream &command() const;
    Stream &console() const;

private:
    ControllerImpl(const Controller &c);
    virtual ~ControllerImpl();

    platypus::DrivePort _drivePorts[2];
    platypus::MultiPort _multiPorts[4];
};