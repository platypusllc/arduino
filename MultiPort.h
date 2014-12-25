/**
 * Platypus Controller MultiPort
 * =============================
 *
 * This class represents the functionality of one of the multiports on a
 * Platypus Controller.  The multiport can be configured for serial, digital,
 * or analog I/O operation, or certain combinations of the above.  It also
 * includes two mechanisms for powering electronics, an always-on, current-
 * limited +5V, and a switchable +VBat.
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MULTIPORT_H
#define PLATYPUS_MULTIPORT_H

#include "Board.h"

namespace Platypus
{
    class MultiPort : public Configurable 
    {
    public:
        void begin();
        void end();
        virtual void loop();

        void setupSerial(int baud, bool rs485, bool txEnabled=false, bool rxEnabled=false);
        Stream serial();

        void setupAnalog(int sampleRate, float scale, float offset, float minVal=-INF, float maxVal=INF);
        float analog();

        void setupDigital(int id, bool output, int value);
        bool read(int id);
        void write(int id, bool value);

        bool isPowered();
        void power(bool enable);
        void powerOn();
        void powerOff();

    protected:
        MultiPort(int channel);
        MultiPort(const &MultiPort);
        virtual ~MultiPort();
    };
}

#endif // PLATYPUS_MULTIPORT_H