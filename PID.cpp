#include "Arduino.h"
#include "PID.h"

double proportional = 0;
double integral = 0;
double derivative = 0;

double previousError = 0;

PID::PID(double kp, double ki, double kd, double setpoint, double maxControl, double minControl) {
  this->kp = kp;  this->ki = ki;  this->kd = kd;

  this->setpoint = setpoint;

  this->maxControl = maxControl;
  this->minControl = minControl;
}

double PID::calculatePID(double actual_value) {
  double error, control;

  error = setpoint - actual_value;

  proportional = error;
  integral = integral + error;
  derivative = error - previousError;
  
  control = proportional * kp + integral * ki + derivative * kd;
  if(control > maxControl) control = maxControl;
  if(control < minControl) control = minControl;
  
  previousError = error;

  return control;
}
