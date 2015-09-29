#include "MultiPort.h"
#include "platypus/Board.h"
#include <Servo.h>

using platypus::impl::MultiPort;

MultiPort::MultiPort()
: isPowered_(false),
, pinUsage_(0)
, port_(nullptr)
{
    // Do nothing.
}

MultiPort::~MultiPort()
{
    // Close existing object if necessary.
    if (port_)
        end();
}

void MultiPort::begin(uint8_t port)
{
    // Close existing object if necessary.
    if (port_)
        end();

    // Store the reference to the port.
    port_ = &platypus::board::MULTI_PORTS[port];

    // Reset port to initial state.
    reset();
}

void MultiPort::end()
{
    // Do nothing if the object is not active.
    if (!port_)
        return;

    // Disable RSxxx receiver
    pinMode(port_->rx_disable, INPUT);
    pinMode(port_->tx_enable, INPUT);
    pinMode(port_->rs485_te, INPUT);
    pinMode(port_->rs485_232, INPUT);
    pinMode(port_->half_duplex, INPUT);
    pinMode(platypus::board::LOOPBACK, INPUT);
    pinMode(port_->pwr_enable, INPUT);

    // Disable any GPIO pins.
    // TODO: do this disabling.

    // Indicate that this object is no longer active.
    port_ = nullptr;
}

float MultiPort::current()
{
    // If the port is not active, return an invalid current.
    if (!port_)
        return std::NAN;

    // Turn on the current select and read the appropriate line.
    digitalWrite(platypus::board::MULTI_SENSE, HIGH);
    int result = analogRead(port_.current);
    digitalWrite(platypus::board::MULTI_SENSE, LOW);

    // Normalize the reading according to the FET spec.
    return (float)result / 3.3f; // TODO: figure out actual constant to use here.
}

void MultiPort::reset()
{
    if (!port_)
        return;

    // Disable RSxxx receiver
    pinMode(port_->rx_disable, OUTPUT);
    digitalWrite(port_->rx_disable, HIGH);

    // Disable RSxxx transmitter
    pinMode(port_->tx_enable, OUTPUT);
    digitalWrite(port_->tx_enable, LOW);

    // Disable RS485 termination resistor
    pinMode(port_->rs485_te, OUTPUT);
    digitalWrite(port_->rs485_te, LOW);

    // Select RS232 (deselect RS485)
    pinMode(port_->rs485_232, OUTPUT);
    digitalWrite(port_->rs485_232, LOW);

    // Disable half-duplex
    pinMode(port_->half_duplex, OUTPUT);
    digitalWrite(port_->half_duplex, LOW);

    // Disable loopback test
    pinMode(platypus::board::LOOPBACK, OUTPUT);
    digitalWrite(platypus::board::LOOPBACK, LOW);

    // Disable 12V output
    pinMode(port_->pwr_enable, OUTPUT);
    digitalWrite(port_->pwr_enable, LOW);
}
