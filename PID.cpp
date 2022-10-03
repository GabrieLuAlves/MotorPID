#include "Arduino.h"
#include "PID.h"

double previousError = 0;

PID::PID(double kp, double ki, double kd, double setpoint) {
  this->kp = kp;  this->ki = ki;  this->kd = kd;

  this->setpoint = setpoint;
}

double PID::calculatePID(double actual_value) {
  double error, control;

  error = setpoint - actual_value;

  this->proportional = error;
  this->integral = integral + error;
  this->derivational = error - previousError;
  
  control =
    this->proportional * kp +
    this->integral * ki +
    this->derivational * kd;
  
  previousError = error;

  return control;
}
