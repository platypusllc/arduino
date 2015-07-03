#ifndef PLATYPUS_COMPONENTS_H
#define PLATYPUS_COMPONENTS_H

#include "Platypus.h"
#include "RoboClaw.h"

namespace platypus 
{
  const int DEFAULT_BUFFER_SIZE = 128;

  class AnalogSensor : public Sensor 
  {
  public:
    AnalogSensor(int channel);

    bool set(char* param, char* value);
    char *name();
    
    void scale(float scale);
    float scale();
    
    void offset(float offset);
    float offset();
    
  private:
    float scale_;
    float offset_;
  };
  
  class ServoSensor : public Sensor 
  {
  public:
    ServoSensor(int channel);
    ~ServoSensor();

    bool set(char* param, char* value);
    char *name();
    
    void position(float velocity);
    float position();
    
  private:
    Servo servo_;
    Servo servo_legacy_; // TODO: remove this once we only have v3+ boards
    float position_;
  };

  class PoweredSensor : public Sensor 
  {
  public:
    PoweredSensor(int channel);
    char *name();
  };

}

#endif // PLATYPUS_COMPONENTS_H
