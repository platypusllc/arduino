/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "Platypus.h"
#include "Board.h"
#include <array>

namespace platypus
{
namespace impl
{

/** This class actually implements the functionality of the Controller. */
class ControllerSingleton
{
public:
    setDriveModule(DrivePort &device);
    setDriveModules(DrivePort device[]);

    setMultiModule(MultiPort &device);
    setMultiModules(MultiPort device[]);

    Led& led() const;
    float battery() const;

    Stream &command() const;
    Stream &console() const;

protected:
    Controller();
    virtual ~Controller();

    Controller(const &Controller) = delete;
    void operator=(const Controller&) = delete;

    std::array<platypus::DrivePort, platypus::board::NUM_DRIVE_PORTS) drivePorts_;
    std::array<platypus::MultiPort, platypus::board::NUM_MULTI_PORTS) multiPorts_;
};

}
}

#endif // PLATYPUS_CONTROLLER_H