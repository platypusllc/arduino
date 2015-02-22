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

namespace Platypus
{
    namespace Serial {
        enum {
            RS232, RS485, RS422,
            NUM_MODES
        } Mode;
    }

    namespace Multi {
        enum {
            RX_P, RX_N, TX_P, TX_N, ANA,
            NUM_PINS
        } Pin
    }

    class MultiPort
    {
    public:
        virtual bool beginSerial(int baud, Serial::Mode mode,
                                 bool tx_enabled=false, bool rx_enabled=false);
        virtual void endSerial();
        virtual Stream &serial() const;

        virtual bool beginAnalog(float scale=1.0, float offset=0.0,
                                 float min_val=-INF, float max_val=INF);
        virtual void endAnalog();
        virtual float analog() const;

        virtual bool beginDigital(Multi::Pin pin, bool is_output, int initial_value);
        virtual void endDigital(Multi::Pin pin);
        virtual bool read(Multi::Pin pin) const;
        virtual void write(Multi::Pin pin, bool value);

        virtual bool isPowered() const;
        virtual void power(bool isPowered);
        virtual void powerOn();
        virtual void powerOff();

        virtual float current() const;

        virtual void reset();

    protected:
        MultiPort() {}
        virtual ~MultiPort() = 0;

    private:
        MultiPort(const &MultiPort);
        MultiPort& operator=(const MultiPort&);
    };
}

#endif // PLATYPUS_MULTIPORT_H