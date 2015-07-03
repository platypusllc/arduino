/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "platypus.h"
#include "board.h"

namespace platypus
{

class ControllerImpl : public platypus::Controller 
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

    platypus::DrivePort _drivePorts[NUM_MOTORS];
    platypus::MultiPort _multiPorts[NUM_SENSORS];
};

}

#endif // PLATYPUS_CONTROLLER_H