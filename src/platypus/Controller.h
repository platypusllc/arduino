/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "Platypus.h"
#include "Board.h"

namespace platypus
{
namespace impl
{

class Controller : public platypus::Controller 
{
public:
    Controller();

    setDrivePort(DrivePort &device);
    setDrivePorts(DrivePort device[]);

    setMultiPort(MultiPort &device);
    setMultiPorts(MultiPort device[]);

    Led& led() const;
    float battery() const;
    Stream &command() const;
    Stream &console() const;

private:
    Controller(const Controller &c) = delete;
    virtual ~Controller();

    platypus::DrivePort _drivePorts[NUM_MOTORS];
    platypus::MultiPort _multiPorts[NUM_SENSORS];
};

}
}

#endif // PLATYPUS_CONTROLLER_H