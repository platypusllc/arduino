/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MULTIPORT_H
#define PLATYPUS_MULTIPORT_H

#include "platypus.h"

namespace Platypus
{
    namespace Pin {
        // This pin enumeration follows the MultiCon connector numbering.
        enum {
            V5 = 1,
            RX_P = 2,
            RX_N = 3,
            V12 = 4,
            TX_P = 5,
            TX_N = 6,
            ANA = 7,
            GND = 8
        } Mask;
    }

    class MultiPortImpl : public platypus::MultiPort
    {
    public:
        void begin(int port);
        void end();

    private:
        bool _isEnabled;
        volatile uint8_t _pinUsageMask;
        uint8_t _port;
    };

}

#endif // PLATYPUS_MULTIPORT_H