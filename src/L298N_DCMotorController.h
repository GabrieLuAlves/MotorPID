#ifndef L298N_DCMotorController
#define L298N_DCMotorController

#include "Arduino.h"

#define FORWARD   1
#define BACKWARD  0


namespace L298N {
  class DCMotorController {
  public:
    DCMotorController(int8_t _in1, int8_t _in2, float _nominalFrequency_rpm);

    // Sets the rotation frequency in RPM
    void setFrequencyRPM(float frequency);
    float getFrequencyRPM();

    void setPwm(uint8_t pwm);
    uint8_t getPwm();

    void setDirection(uint8_t direction);
    uint8_t getDirection();

    void update();
    
  private:
    int8_t  in1;
    int8_t  in2;

    uint8_t pwm = 0;
    uint8_t direction = 1;
  };
};

#endif
