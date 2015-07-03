/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_DRIVE_PORT_H
#define PLATYPUS_DRIVE_PORT_H

#include "platypus.h"

namespace platypus
{
namespace impl
{

class DrivePort : public platypus::DrivePort
{
public:
    void begin(int port);
    void end();

private:
    float command_;
    bool isPowered_;
    uint8_t port_;
    Servo servo_;
};

}
}

#endif // PLATYPUS_DRIVE_PORT_H