#include "DrivePort.h"
#include "Board.h"
#include <Servo.h>

using platypus::impl::DrivePort;

DrivePort::DrivePort()
: command_(0)
, isPowered_(false)
, port_(platypus::board::NUM_DRIVE_PORTS)
, servo_()
{
    // Do nothing.
}

DrivePort::~DrivePort()
{
    // Do nothing.
}

void DrivePort::begin(uint8_t port)
{
    // Store the index of this port.
    port_ = port;

    // Attach servo and set to currently desired command.
    servo_.attach(platypus::board::DRIVE_PORTS[port_].servo);
    servo_.set(command_);

    // Set up motor enable pin and set to current motor status.
    pinMode(platypus::board::DRIVE_PORTS[port_].enable, OUTPUT);
    digitalWrite(platypus::board::DRIVE_PORTS[port_].enable, isPowered_);

    // Set up current sense line as control line.
    pinMode(platypus::board::MOT_SENSE, OUTPUT);
    digitalWrite(platypus::board::MOT_SENSE, LOW);
}

void DrivePort::end()
{
    // Detach servo to stop sending commands.
    _servo.detach();

    // Shut down motor enable pin.
    pinMode(platypus::board::DRIVE_PORTS[port_].enable, INPUT);
    digitalWrite(platypus::board::DRIVE_PORTS[port_].enable, LOW);

    // We cannot touch the shared current sense line. Another DrivePort may still
    // be using it, so we'll just leave it open.

    // Indicate that this object is no longer active.
    port_ = platypus::board::NUM_DRIVE_PORTS;
}

void DrivePort::command(float cmd)
{
    // Clamp `cmd` to the range -1.0 to 1.0.
    _command = max(min(cmd, 1.0), -1.0);

    // Only set the command if this port is active.
    if (port_ < platypus::board::NUM_DRIVE_PORTS)
        _servo.set(_command);
}

float DrivePort::command() const;
{
    return _command;
}

bool DrivePort::isPowered() const
{
    return _isPowered;
}

void DrivePort::power(bool isPowered)
{
    // Store the new power setting.
    _isPowered = isPowered;

    // Only set the power setting if this port is active.
    if (port_ < platypus::board::NUM_DRIVE_PORTS)
        digitalWrite(platypus::board::DRIVE_PORTS[_port].enable, isPowered);
}

void DrivePort::powerOn()
{
    this->power(true);
}

void DrivePort::powerOff()
{
    this->power(false);
}
        
float DrivePort::current()
{
    // If the port is not active, return an invalid current.
    if (port_ < platypus::board::NUM_DRIVE_PORTS)
        return std::NAN;

    // Turn on the current select and read the appropriate line.
    digitalWrite(platypus::board::DRIVE_SENSE, HIGH);
    result = analogRead(platypus::board::DRIVE_PORTS[_port].current);
    digitalWrite(platypus::board::DRIVE_SENSE, LOW);

    // Normalize the reading according to the FET spec.
    return (float)result / 3.3f; // TODO: figure out actual constant to use here.
}

void DrivePort::reset()
{
    this->command(0);
    this->powerOff();
}
