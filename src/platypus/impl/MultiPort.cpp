#include "MultiPort.h"
#include "Board.h"
#include <Servo.h>

using platypus::impl::MultiPort;

MultiPort::MultiPort()
: isPowered_(false),
, pinUsage_(0)
, port_(platypus::board::NUM_MULTI_PORTS)
{
    // Do nothing.
}

MultiPort::~MultiPort()
{
    // Do nothing.
}

void MultiPort::begin(uint8_t port)
{
    // Store the reference to the port.
    port_ = &platypus::board::MULTI_PORT[port_];

    // Reset port to initial state.
    reset();
}

void MultiPort::end()
{
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
}

float MultiPort::current()
{
    digitalWrite(platypus::board::MULTI_SENSE, HIGH);
    int result = analogRead(port_.current);
    digitalWrite(platypus::board::MULTI_SENSE, LOW);
    return (float)result / 3.3;
}

void MultiPort::reset()
{
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
