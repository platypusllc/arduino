/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_DRIVE_PORT_H
#define PLATYPUS_DRIVE_PORT_H

#include "Platypus.h"
#include "platypus/board.h"
#include <Servo.h>

namespace platypus
{
namespace impl
{

class DrivePort : public ::platypus::DrivePort
{
public:
    void begin(uint8_t port);
    void end();

	void command(float cmd) override;
    float command() const override;
    bool isPowered() const override;
    void power(bool isPowered) override;
    void powerOn() override;
    void powerOff() override;
    float current() override;
    void reset() override;
protected:
	DrivePort();
	virtual ~DrivePort();

    float command_;
    bool isPowered_;
    const ::platypus::board::DriveConfig *port_;
    Servo servo_;

private:
	DrivePort(DrivePort const &) = delete;
	void operator=(DrivePort const &) = delete;

	friend ::platypus::Controller;
};

}
}

#endif // PLATYPUS_DRIVE_PORT_H