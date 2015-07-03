/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_DRIVE_PORT_H
#define PLATYPUS_DRIVE_PORT_H

#include "platypus.h"

namespace platypus
{

class DrivePortImpl : public platypus::DrivePort
{
public:
    void begin(int port);
    void end();

private:
    float _command;
    bool _isPowered;
    uint8_t _port;
    Servo _servo;
};

}

#endif // PLATYPUS_DRIVE_PORT_H