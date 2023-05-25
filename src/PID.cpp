#include "Arduino.h"
#include "PID.h"


PID::PID(float _kp, float _ki, float _kd, float _setpoint) :
  kp{_kp},
  ki{_ki},
  kd{_kd},
  setpoint{_setpoint},
  errorIntegral{0.0},
  lastError{0.0} {

}

void PID::setSetpoint(float _setpoint) {
  setpoint = _setpoint;  
}

float PID::getSetpoint() {
  return setpoint;
}


float PID::calculate(float actualValue) {
  float error = 0;
  float control = 0;

  error = setpoint - actualValue;
  errorIntegral += error;
  
  control =
    error * kp +
    errorIntegral * ki +
    (error - lastError) * kd;
  
  lastError = error;

  return control;
}
