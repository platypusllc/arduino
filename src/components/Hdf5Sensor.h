#ifndef PLATYPUS_HDF5_SENSOR_H
#define PLATYPUS_HDF5_SENSOR_H

#include "Components.h"

namespace platypus 
{
    class Hds5 : public Sensor 
    {
    public:
        Hds5(int channel);
        char *name();
        void onSerial();

    private:
        char recv_buffer_[DEFAULT_BUFFER_SIZE];
        unsigned int recv_index_;
    };
}

#endif // PLATYPUS_HDF5_SENSOR_H