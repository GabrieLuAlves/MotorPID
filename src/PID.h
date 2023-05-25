#ifndef PID_H
#define PID_H


class PID {

public:
  PID(float _kp, float _ki, float _kd, float _setpoint);
  float calculate(float actualValue);

  void setSetpoint(float _setpoint);
  float getSetpoint();

private:
  float setpoint;
  float kp = 0, ki = 0, kd = 0;

  float errorIntegral = 0;
  float lastError = 0;
};

#endif
