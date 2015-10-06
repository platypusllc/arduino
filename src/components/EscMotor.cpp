#include "EscMotor.h"

using namespace platypus;

void VaporPro::arm()
{
    disable();
    delay(500);
    enable();

    velocity(1.0);
    delay(5500);

    velocity(-1.0);
    delay(3500);

    velocity(0.0);
    delay(8500);
}

const String &VaporPro::name() const
{
    return "VaporPro";
}

void HobbyKingBoat::arm()
{
    disable();
    delay(1000);

    velocity(1.0);
    enable();
    delay(3000);

    velocity(0.0);
    delay(3000);
}

const String &HobbyKingBoat::name() const
{
    return "HobbyKingBoat";
}

void SeaKing::arm()
{
    disable();
    delay(500);

    velocity(1.0);
    enable();
    delay(3000);

    velocity(0.0);
    delay(2000);
}

const String &SeaKing::name() const
{
    return "SeaKing";
}

void Swordfish::arm()
{
    disable();
    delay(500);

    velocity(1.0);
    enable();
    delay(5000);

    velocity(0.0);
    delay(3000);
}

const String &Swordfish::name() const
{
    return "Swordfish";
}