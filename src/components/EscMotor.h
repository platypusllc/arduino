#ifndef PLATYPUS_ESC_MOTOR_H
#define PLATYPUS_ESC_MOTOR_H

#include "Components.h"

namespace platypus
{
    class VaporPro : public DriveModule 
    {
    public:
        void arm();
        const String &name() const override;
    };

    class HobbyKingBoat : public DriveModule 
    {
    public:
        void arm();
        const String &name() const override;
    };
    
    class SeaKing : public DriveModule 
    {
    public:
        void arm();
        const String &name() const override;
    };

    class Swordfish : public DriveModule 
    {
    public:
        void arm();
        const String &name() const override;
    };
}

#endif // PLATYPUS_ESC_MOTOR_H
