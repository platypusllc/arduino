/**
 * Platypus Controller Module
 * ==========================
 *
 * Modules represent device-specific control code that can be attached to a
 * DrivePort or a MultiPort.  This is where the majority of device logic is
 * normally contained.
 *
 * This library includes some modules for commonly used sensors and motor
 * drivers, but you can write your own to extend functionality to new devices.
 *
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MODULE_H
#define PLATYPUS_MODULE_H

#include "DrivePort.h"
#include "MultiPort.h"

namespace platypus
{
    class DriveModule : public Configurable
    { 
    public:
        virtual void begin(DrivePort &port);
        virtual void end();
        virtual void loop();
        virtual void arm();
        virtual void disarm();
        virtual String name() const = 0;

    protected:
        virtual ~DriveModule() = 0;
    };

    class MultiModule : public Configurable
    { 
    public:
        virtual void begin(MultiPort &port);
        virtual void end();
        virtual void loop();
        virtual String name() const = 0;

    protected:
        virtual ~MultiModule() = 0;
    };
}

#endif // PLATYPUS_MODULE_H