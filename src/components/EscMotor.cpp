#include "EscMotor.h"

using namespace platypus;

void VaporPro::arm()
{
    port_.drivePowerOff();
    delay(500);
    port_.drivePowerOn();

    port_.command(1.0);
    delay(5500);

    port_.command(-1.0);
    delay(3500);

    port_.command(0.0);
    delay(8500);
}

const String &VaporPro::name() const
{
    return "VaporPro";
}

void HobbyKingBoat::arm()
{
    port_.drivePowerOff();
    delay(1000);

    port_.command(1.0);
    port_.drivePowerOn();
    delay(3000);

    port_.command(0.0);
    delay(3000);
}

const String &HobbyKingBoat::name() const
{
    return "HobbyKingBoat";
}

void SeaKing::arm()
{
    port_.drivePowerOff();
    delay(500);

    port_.command(1.0);
    port_.drivePowerOn();
    delay(3000);

    port_.command(0.0);
    delay(2000);
}

const String &SeaKing::name() const
{
    return "SeaKing";
}

void Swordfish::arm()
{
    port_.drivePowerOff();
    delay(500);

    port_.command(1.0);
    port_.drivePowerOn();
    delay(5000);

    port_.command(0.0);
    delay(3000);
}

const String &Swordfish::name() const
{
    return "Swordfish";
}