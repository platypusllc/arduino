/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "Platypus.h"
#include "Board.h"
#include <adk.h>
#include <array>

namespace platypus
{
namespace impl
{

class Controller : public platypus::Controller 
{
protected:
    Controller();
    virtual ~Controller();

    Controller(const &Controller) = delete;
    void operator=(const Controller&) = delete;

    std::array<platypus::DrivePort, platypus::board::NUM_DRIVE_PORTS) drivePorts_;
    std::array<platypus::DriveModule, platypus::board::NUM_DRIVE_PORTS) driveModules_;
    
    std::array<platypus::MultiPort, platypus::board::NUM_MULTI_PORTS) multiPorts_;
    std::array<platypus::MultiModule, platypus::board::NUM_MULTI_PORTS) multiModules_;

    // ADK USB Host
    USBHost usb_;
    ADK adk_;

    // Android send/receive buffers
    const size_t INPUT_BUFFER_SIZE = 512;
    char command_buffer_[INPUT_BUFFER_SIZE+1];
    char console_buffer_[INPUT_BUFFER_SIZE+1];

    const size_t OUTPUT_BUFFER_SIZE = 576;
    char output_buffer_[OUTPUT_BUFFER_SIZE+3];

    // Connectivity to the Android server.
    platypus::ServerStatus serverStatus_;
};

}
}

#endif // PLATYPUS_CONTROLLER_H