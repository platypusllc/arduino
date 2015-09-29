/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "Platypus.h"
#include "platypus/Board.h"
#include "AdkStream.h"
#include <adk.h>
#include <array>

namespace platypus
{
namespace impl
{

class Controller : public ::platypus::Controller 
{
public:
    Controller(Controller const &) = delete;
    void operator=(Controller const &) = delete;

    void begin() override;

    // TODO: figure out how to limit this to friend access.
    static Controller &instance();

    // TODO: figure out how to limit this to friend access.
    std::array<platypus::DriveModule*, platypus::board::NUM_DRIVE_PORTS> driveModules_;
    std::array<platypus::MultiModule*, platypus::board::NUM_MULTI_PORTS> multiModules_;

private:
    Controller();
    virtual ~Controller();
    
protected:
    std::array<platypus::DrivePort*, platypus::board::NUM_DRIVE_PORTS> drivePorts_;
    std::array<platypus::MultiPort*, platypus::board::NUM_MULTI_PORTS> multiPorts_;

    // ADK USB Host
    USBHost usb_;
    ADK adk_;
    AdkStream stream_;

    // Connectivity to the Android server.
    platypus::Status status_;

    // Allow protected access for the communication handlers.
    friend void handleCommand(Controller &controller, const char *buffer);
    friend void serialStreamLoop(void *data);
    friend void adkStreamLoop(void *data);
};

}
}

#endif // PLATYPUS_CONTROLLER_H
