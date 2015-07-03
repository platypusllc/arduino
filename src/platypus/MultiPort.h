/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MULTIPORT_H
#define PLATYPUS_MULTIPORT_H

#include "platypus.h"

namespace platypus
{
namespace impl
{

namespace Pin {
    // This pin enumeration follows order of the MultiCon pinout.
    enum {
        V5   = 0x01,
        RX_P = 0x02,
        RX_N = 0x04,
        V12  = 0x08,
        TX_P = 0x10,
        TX_N = 0x20,
        ANA  = 0x40,
        GND  = 0x80
    } Mask;
}

class MultiPort : public platypus::MultiPort
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
}

#endif // PLATYPUS_MULTIPORT_H