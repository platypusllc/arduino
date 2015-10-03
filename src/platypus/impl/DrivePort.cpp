#include "DrivePort.h"

using platypus::impl::DrivePort;

DrivePort::DrivePort()
: command_(0)
, isDrivePowered_(false)
, isServoPowered_(false)
, port_(nullptr)
, servo_()
{
    // Do nothing.
}

DrivePort::~DrivePort()
{
    // Close existing object if necessary.
    if (port_)
        end();
}

void DrivePort::begin(uint8_t port)
{
    // Close existing object if necessary.
    if (port_)
        end();

    // Store the reference to the port.
    port_ = &platypus::board::DRIVE_CONFIGS[port];

    // Attach servo and set to currently desired command.
    servo_.attach(port_->servo);
    servo_.writeMicroseconds(command_ * 500 + 1500);

    // Set up drive enable pin and set to current drive status.
    pinMode(port_->drive_enable, OUTPUT);
    digitalWrite(port_->drive_enable, isDrivePowered_);

    // Set up servo enable pin and set to current servo status.
    pinMode(port_->servo_enable, OUTPUT);
    digitalWrite(port_->servo_enable, isServoPowered_);

    // Set up current sense line as control line.
    pinMode(platypus::board::DRIVE_SENSE, OUTPUT);
    digitalWrite(platypus::board::DRIVE_SENSE, LOW);

    pinMode(platypus::board::MULTI_SENSE, OUTPUT);
    digitalWrite(platypus::board::MULTI_SENSE, LOW);
}

void DrivePort::end()
{
    // Do nothing if the object is not active.
    if (!port_)
        return;

    // Detach servo to stop sending commands.
    servo_.detach();

    // Shut down drive enable pin.
    pinMode(port_->drive_enable, INPUT);
    digitalWrite(port_->drive_enable, LOW);

    // Shut down servo enable pin.
    pinMode(port_->drive_enable, INPUT);
    digitalWrite(port_->drive_enable, LOW);

    // We cannot touch the shared current sense line. Another DrivePort may still
    // be using it, so we'll just leave it open.

    // Indicate that this object is no longer active.
    port_ = nullptr;
}

void DrivePort::command(float cmd)
{
    // Clamp `cmd` to the range -1.0 to 1.0.
    command_ = platypus::clip(cmd, -1.0f, 1.0f);

    // Only set the command if this port is active.
    if (port_)
        servo_.writeMicroseconds(command_ * 500 + 1500);
}

float DrivePort::command() const
{
    return command_;
}

bool DrivePort::isDrivePowered() const
{
    return isDrivePowered_;
}

void DrivePort::drivePower(bool isPowered)
{
    // Store the new power setting.
    isDrivePowered_ = isPowered;

    // Only set the power setting if this port is active.
    if (port_)
        digitalWrite(port_->drive_enable, isPowered);
}

void DrivePort::drivePowerOn()
{
    this->drivePower(true);
}

void DrivePort::drivePowerOff()
{
    this->drivePower(false);
}

bool DrivePort::isServoPowered() const
{
    return isServoPowered_;
}

void DrivePort::servoPower(bool isPowered)
{
    // Store the new power setting.
    isServoPowered_ = isPowered;

    // Only set the power setting if this port is active.
    if (port_)
        digitalWrite(port_->drive_enable, isPowered);
}

void DrivePort::servoPowerOn()
{
    this->servoPower(true);
}

void DrivePort::servoPowerOff()
{
    this->servoPower(false);
}
        
float DrivePort::current() const
{
    // If the port is not active, return an invalid current.
    if (!port_)
        return std::numeric_limits<double>::quiet_NaN();

    // Turn on the current select and read the appropriate line.
    digitalWrite(platypus::board::MULTI_SENSE, LOW);
    digitalWrite(platypus::board::DRIVE_SENSE, HIGH);
    float result = analogRead(port_->current);
    digitalWrite(platypus::board::DRIVE_SENSE, LOW);
    digitalWrite(platypus::board::MULTI_SENSE, LOW);

    // Normalize the reading according to the FET spec.
    return (float)result / 3.3f; // TODO: figure out actual constant to use here.
}

void DrivePort::reset()
{
    this->command(0);
    this->drivePowerOff();
    this->servoPowerOff();
}
