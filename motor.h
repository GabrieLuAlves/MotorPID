#ifndef MOTOR_H
#define MOTOR_H

#include "encoder.h"
#include "PID.h"

enum Direction {
  FORWARD,
  BACKWARD,
  RELEASE
};

class Motor {
public:
  Motor(byte, byte, byte);
  
  void setSpeed(float);
  
  void setDirection(Direction);

  void setPwm(byte);

  byte getPwm();
private:    
  byte ENA; // MUST be a pwm pin
  byte IN1;
  byte IN2;
  byte pwm;
};

#endif
