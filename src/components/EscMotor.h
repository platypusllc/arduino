#ifndef PLATYPUS_ESC_MOTOR_H
#define PLATYPUS_ESC_MOTOR_H

#include "Components.h"

namespace platypus
{
    class VaporPro : public DriveModule 
    {
    public:
        VaporPro(int channel) : Motor(channel) {}
        void arm();
    };

    class HobbyKingBoat : public DriveModule 
    {
    public:
        HobbyKingBoat(int channel) : Motor(channel) {}
        void arm();
    };
    
    class Seaking : public DriveModule 
    {
    public:
        Seaking(int channel) : Motor(channel) {}
        void arm();
    };

    class Swordfish : public DriveModule 
    {
    public:
        Swordfish(int channel) : Motor(channel) {}
        void arm();
    };
}

#endif // PLATYPUS_ESC_MOTOR_H
