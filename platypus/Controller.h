/**
 * Platypus Controller
 * ===================
 *
 * This class represents the hardware abstraction for a Platypus Controller.
 * The controller provides an interface from the Android server to hardware
 * devices such as motors and sensors.
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_CONTROLLER_H
#define PLATYPUS_CONTROLLER_H

#include "DrivePort.h"
#include "MultiPort.h"

namespace platypus
{
    class Configurable
    {
    public:     
        virtual bool set(String param, String value);
    };

    class Controller : Configurable {
    public:
        virtual bool setDrive(int which, DriveModule &device);
        virtual bool setDrives(DriveModule device[]);
        virtual int numDrives() const;

        virtual bool setMulti(int which, MultiModule &device);
        virtual bool setMultis(MultiModule device[]);
        virtual int numMultis() const;

        virtual Led& led() const;
        virtual float battery() const;
        virtual Stream &command() const;
        virtual Stream &console() const;

    protected:
        Controller() {}
        virtual ~Controller() = 0;

    private:
        Controller(const &Controller);
        Controller& operator=(const Controller&);
    };

    class Led 
    { 
    public:
        virtual void rgb(int red, int green, int blue);
        virtual void R(int red);
        virtual int R();
        virtual void G(int green);
        virtual int G();
        virtual void B(int blue);
        virtual int B();

    protected:
        Led() {}
        virtual ~Led() = 0;

    private:
        Led(const &Led);
        Led& operator=(const Led&);
    };
}

#endif // PLATYPUS_CONTROLLER_H