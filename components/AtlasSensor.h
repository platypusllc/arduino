#ifndef PLATYPUS_ATLAS_SENSOR_H
#define PLATYPUS_ATLAS_SENSOR_H

#include "Platypus.h"

namespace platypus
{
    class AtlasSensor : public Sensor 
    {
    public:
        AtlasSensor(int channel);
        char *name();
        void onSerial();
        
    private:
        char recv_buffer_[DEFAULT_BUFFER_SIZE];
        unsigned int recv_index_;
    };
}

#endif // PLATYPUS_ATLAS_SENSOR_H