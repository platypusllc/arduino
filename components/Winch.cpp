#include "Winch.h"

using namespace platypus;

// TODO: move these somewhere reasonable
// Default gains for the Roboclaw.
/*#define Kp 0x00010000
#define Ki 0x00008000
#define Kd 0x00004000
#define Qpps 44000
*/

//Velocity PID coefficients
#define Kp 2
#define Ki 4
#define Kd 0
#define Qpps 44000 //3600

//Position PID coefficients
#define PosKp 2500
#define PosKi 0
#define PosKd 20000
#define KiMax 0
#define DeadZone 5 //10
#define Min 50
#define Max 1950

#define addr 0x80

Winch::Winch(int channel, uint8_t address)
: Sensor(channel)
, roboclaw_(platypus::SERIAL_PORTS[channel], 10000)
, address_(address)
, desired_position_(0)
, desired_velocity_(0)
, desired_acceleration_(12000)
{  
  // Enable +12V output.
  pinMode(board::SENSOR[channel].PWR_ENABLE, OUTPUT);
  digitalWrite(board::SENSOR[channel].PWR_ENABLE, HIGH);
  
  // TODO: specifically enable e-stop line.
  // (Right now it is just pulled up by default.)
  
  // Start up Roboclaw.
  roboclaw_.begin(38400);
}

char* Winch::name()
{
  return "winch";
}

bool Winch::set(char* param, char* value)
{
  // Set winch position
  if (!strncmp("p", param, 2))
  {
    uint32_t pos = atol(value);
    
    position(pos);
    return true;
  }
  else if (!strncmp("v", param, 2))
  {
    int32_t vel = atol(value);
    
    velocity(vel);
    return true;    
  }
  else if (!strncmp("reset", param, 6))
  {
    
    reset();
    return true;
  }
  // Return false for unknown command.
  else
  {

    return false;
  }
}

void Winch::reset()
{
  roboclaw_.ResetEncoders(address_);
}

void Winch::position(uint32_t pos)
{
  desired_position_ = pos;
  roboclaw_.SetM1PositionPID(addr, PosKd, PosKp, PosKi, KiMax, DeadZone, Min, Max);
}

void Winch::velocity(int32_t vel)
{
  desired_velocity_ = vel;
  roboclaw_.SetM1VelocityPID(addr, Kd, Kp, Ki, Qpps);
  roboclaw_.SpeedAccelDistanceM1(addr, 
                                 desired_acceleration_, 
                                 desired_velocity_,
                                 desired_position_);     
}

uint32_t Winch::encoder(bool *valid)
{
  uint32_t enc1 = roboclaw_.ReadEncM1(addr, NULL, valid);
  return enc1;
}
