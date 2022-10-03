#ifndef PID_H
#define PID_H

class PID {
public:
  PID(double, double, double, double);
  
  double calculatePID(double);

  double setpoint;
  double kp = 0, ki = 0, kd = 0;
  
  double proportional = 0, integral = 0, derivational = 0;

};

#endif
