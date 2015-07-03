#ifndef PLATYPUS_ESC_MOTOR_H
#define PLATYPUS_ESC_MOTOR_H

#include "Platypus.h"

namespace platypus
{
    class VaporPro : public Motor 
    {
    public:
        VaporPro(int channel) : Motor(channel) {}
        void arm();
    };

    class HobbyKingBoat : public Motor 
    {
    public:
        HobbyKingBoat(int channel) : Motor(channel) {}
        void arm();
    };
    
    class Seaking : public Motor 
    {
    public:
        Seaking(int channel) : Motor(channel) {}
        void arm();
    };

    class Swordfish : public Motor 
    {
    public:
        Swordfish(int channel) : Motor(channel) {}
        void arm();
    };
}

#endif // PLATYPUS_ESC_MOTOR_H
