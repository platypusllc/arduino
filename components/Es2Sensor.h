#ifndef PLATYPUS_ES2_SENSOR_H
#define PLATYPUS_ES2_SENSOR_H

namespace platypus 
{
    class Es2Sensor : public Sensor 
    {
    public:
        Es2Sensor(int channel);
        char *name();
        void loop();
        void onSerial();

    private:
        char recv_buffer_[DEFAULT_BUFFER_SIZE];
        unsigned int recv_index_;
    };
}

#endif // PLATYPUS_ES2_SENSOR_H