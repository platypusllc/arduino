/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MULTIPORT_H
#define PLATYPUS_MULTIPORT_H

#include "platypus.h"

namespace Platypus
{
    class LedImpl : public platypus::Led
    {
      void begin();
      void end();

    private:
        int r_, g_, b_;
    };
}

#endif // PLATYPUS_MULTIPORT_H