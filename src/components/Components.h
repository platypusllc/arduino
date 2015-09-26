#ifndef PLATYPUS_COMPONENTS_H
#define PLATYPUS_COMPONENTS_H

#include "Platypus.h"
#include <Servo.h>

namespace platypus 
{
  constexpr size_t DEFAULT_BUFFER_SIZE = 128;

  class AnalogSensor : public MultiModule 
  {
  public:
    AnalogSensor() = default;

    void begin(MultiPort &port) override;
    void end() override;

    bool set(const String &param, const String &value) override;
    const String &name() const override;

    void scale(float scale);
    float scale();
    
    void offset(float offset);
    float offset();
    
  private:
    float scale_ = 1.0f;
    float offset_ = 0.0f;
  };
  
  class ServoSensor : public MultiModule 
  {
  public:
    ServoSensor() = default;

    void begin(MultiPort &port) override;
    void end() override;

    bool set(const String &param, const String &value) override;
    const String &name() const override;
    
    void position(float velocity);
    float position();
    
  private:
    Servo servo_;
    float position_ = 0.0f;
  };

  class PoweredSensor : public MultiModule 
  {
  public:
    PoweredSensor() = default;

    void begin(MultiPort &port) override;
    void end() override;

    bool set(const String &param, const String &value) override;

    const String &name() const override;
  };
}

#endif // PLATYPUS_COMPONENTS_H
