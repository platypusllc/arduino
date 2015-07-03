#ifndef PLATYPUS_WINCH_H
#define PLATYPUS_WINCH_H

#include "Platypus.h"
#include "RoboClaw.h"

namespace platypus
{
    class Winch : public Sensor 
    {
    public:
        Winch(int channel, uint8_t address);
        char *name();
        bool set(char* param, char* value);
        
        void reset();

        void velocity(int32_t pos);
        void position(uint32_t pos);
        uint32_t encoder(bool *valid = NULL);

    private:
        RoboClaw roboclaw_;
        uint8_t address_;
        uint32_t desired_position_;
        int32_t desired_velocity_;
        uint32_t desired_acceleration_;
    };
}

#endif // PLATYPUS_WINCH_H