/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "Platypus.h"
#include "platypus/Board.h"
#include "platypus/impl/Led.h"
#include "AdkStream.h"
#include <adk.h>
#include <array>

namespace platypus
{
namespace impl
{

void driveLoop(void *data);
void multiLoop(void *data);

class Controller : public ::platypus::Controller 
{
public:
    Controller(Controller const &) = delete;
    void operator=(Controller const &) = delete;

    void begin() override;
    void end() override;
    void reset() override;

    platypus::DrivePort &drive(unsigned int which) override;
    const platypus::DrivePort &drive(unsigned int which) const override;
    unsigned int numDrives() const override;
    bool setDriveModule(unsigned int which, DriveModule &device) override;

    platypus::MultiPort &multi(unsigned int which) override;
    const platypus::MultiPort &multi(unsigned int which) const override;
    unsigned int numMultis() const override;
    bool setMultiModule(unsigned int which, MultiModule &device) override;

    platypus::Led& led() override;
    const platypus::Led& led() const override;
    float battery() const override;
    platypus::Status status() const override;
    bool isConnected() const override;

    Stream &stream() override;

    bool set(const String &param, const String &value);

    // TODO: figure out how to limit this to friend access.
    static Controller &instance();

private:
    Controller();
    virtual ~Controller();
    
protected:
    std::array<platypus::DrivePort*, platypus::board::NUM_DRIVE_PORTS> drivePorts_;
    std::array<platypus::MultiPort*, platypus::board::NUM_MULTI_PORTS> multiPorts_;

    std::array<platypus::DriveModule*, platypus::board::NUM_DRIVE_PORTS> driveModules_;
    std::array<platypus::MultiModule*, platypus::board::NUM_MULTI_PORTS> multiModules_;

    platypus::impl::Led led_;

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
    
    friend void driveLoop(void *data);
    friend void multiLoop(void *data);
};

}
}

#endif // PLATYPUS_CONTROLLER_H
