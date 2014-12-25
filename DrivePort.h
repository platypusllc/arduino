/**
 * Platypus Controller DrivePort
 * =============================
 *
 * This class represents the functionality of one of the driveports on a
 * Platypus Controller.  The driveport can be configured to command a servo or
 * motor controller such as an ESC.
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_DRIVE_PORT_H
#define PLATYPUS_DRIVE_PORT_H

#include "Board.h"

namespace platypus
{
    class DrivePort : public Configurable
    { 
    public:
        void begin();
        void end();
        virtual void loop();

        virtual void arm() = 0;
        void command(float cmd);
        float command();
        
        void enable(bool enabled);
        bool enabled();
        
        void enable();
        void disable();
        
        float current();

    protected:
        DrivePort(int channel);
        DrivePort(const &DrivePort);
        virtual ~DrivePort();
    };
}

#endif // PLATYPUS_DRIVE_PORT_H