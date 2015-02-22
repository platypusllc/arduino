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

namespace platypus
{
    class DrivePort
    { 
    public:
        virtual void command(float cmd);
        virtual float command() const;
        
        virtual bool isPowered() const;
        virtual void power(bool enabled);
        virtual void powerOn();
        virtual void powerOff();
        
        virtual float current();

    protected:
        DrivePort() {}
        virtual ~DrivePort() = 0;

    private:
        DrivePort(const &DrivePort);
        DrivePort& operator=(const DrivePort&);
    };
}

#endif // PLATYPUS_DRIVE_PORT_H