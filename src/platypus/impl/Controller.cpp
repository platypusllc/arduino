#include "Controller.h"
#include "Communication.h"
#include "platypus/Board.h"
#include <Arduino.h>
#include <Scheduler.h>

using platypus::impl::Controller;

uint32_t swap(uint32_t bytes)
{
    return ((bytes << 24) & 0xFF000000)
            | ((bytes <<  8) & 0x00FF0000)
            | ((bytes >>  8) & 0x0000FF00)
            | ((bytes >> 24) & 0x000000FF);
}

void platypus::impl::driveLoop(void *data)
{
    size_t driveIdx = (size_t)data;
    Controller &controller = static_cast<Controller&>(platypus::getController());
    while (true)
    {
       controller.driveModules_[driveIdx]->loop();
    }
}

void platypus::impl::multiLoop(void *data)
{
    size_t multiIdx = (size_t)data;
    Controller &controller = static_cast<Controller&>(platypus::getController());
    while (true)
    {
        controller.multiModules_[multiIdx]->loop();
    }
}

Controller::Controller()
: adk_(&usb_,
       platypus::board::ADK_COMPANY_NAME, platypus::board::ADK_APPLICATION_NAME,
       platypus::board::ADK_ACCESSORY_NAME, platypus::board::ADK_VERSION_NUMBER,
       platypus::board::ADK_URL, platypus::board::ADK_SERIAL_NUMBER)
, stream_(adk_, Serial)
, status_(platypus::Status::DISCONNECTED)
{
    // Do nothing.
}

Controller::~Controller()
{
    // Do nothing.
    // This should never be reached, Controller is only instantiated as a singleton.
}

Controller &Controller::instance()
{
    static Controller instance;
    return instance;
}

void Controller::begin()
{
    // Latch power shutdown line high to keep board from turning off.
    pinMode(platypus::board::PWR_KILL, OUTPUT);
    digitalWrite(platypus::board::PWR_KILL, HIGH);

    // Initialize serial console.
    Serial.begin(115200);

    // Print startup header to the command stream.
    sendHeader(stream());

    // Initialize LED.
    led_.begin();

    // Start update loops for each drive module.
    for (size_t driveIdx = 0; driveIdx < platypus::board::NUM_DRIVE_PORTS; ++driveIdx)
    {
        Scheduler.start(driveLoop, (void *)driveIdx);
    }

    // Start update loops for each multi module.
    for (size_t multiIdx = 0; multiIdx < platypus::board::NUM_DRIVE_PORTS; ++multiIdx)
    {
        Scheduler.start(multiLoop, (void *)multiIdx);
    }

    // Create update loops for command stream.
    Scheduler.start(platypus::impl::adkStreamLoop, (void *)this);
    Scheduler.start(platypus::impl::serialStreamLoop, (void *)this);
}

void Controller::end()
{
    // This is a weird error condition, so we are going to reset the board.
    reset();
}

void Controller::reset()
{
    // Lower the power shutdown line high to shut the board off.
    digitalWrite(platypus::board::PWR_KILL, LOW);
    delay(100);
}

platypus::DrivePort &Controller::drive(unsigned int which)
{
    // TODO: add dummy port.
    return *drivePorts_[which];
}

const platypus::DrivePort &Controller::drive(unsigned int which) const
{
    return drive(which);
}

unsigned int Controller::numDrives() const
{
    return drivePorts_.size();
}

bool Controller::setDriveModule(size_t which, platypus::DriveModule &device)
{
    if (which >= drivePorts_.size())
        return false;
    
    driveModules_[which] = &device;
    return true;
}

platypus::MultiPort &Controller::multi(unsigned int which)
{
    // TODO: add dummy port.
    return *multiPorts_[which];
}

const platypus::MultiPort &Controller::multi(unsigned int which) const
{
    // TODO: add dummy port.
    return multi(which);
}

unsigned int Controller::numMultis() const
{
    return multiPorts_.size();
}

bool Controller::setMultiModule(unsigned int which, platypus::MultiModule &device)
{
    if (which >= multiPorts_.size())
        return false;
    
    multiModules_[which] = &device;
    return true;
}

platypus::Led& Controller::led()
{
    return led_;
}

const platypus::Led& Controller::led() const
{
    return led();
}

float Controller::battery() const
{
    // TOOD: implement this correctly.
    return 0.0;
}

platypus::Status Controller::status() const
{
    return Status::DISCONNECTED;
}

bool Controller::isConnected() const
{
    return false;
}

Stream &Controller::stream()
{
    return stream_;
}

bool Controller::set(const String &param, const String &value)
{
    return false;
}