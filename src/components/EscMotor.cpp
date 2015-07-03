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

void Seaking::arm()
{
  disable();
  delay(500);

  velocity(1.0);
  enable();
  delay(3000);

  velocity(0.0);
  delay(2000);
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