#include "L298N_DCMotorController.h"


namespace L298N {
  DCMotorController::DCMotorController(int8_t _in1, int8_t _in2, float _nominalFrequency_rpm) :
    in1{_in1},
    in2{_in2} {
  
  }

  void DCMotorController::setPwm(uint8_t _pwm) {
    pwm = _pwm;
    update();
  }
  
  uint8_t DCMotorController::getPwm() {
    return pwm;
  }

  void DCMotorController::setDirection(uint8_t _direction) {
    direction = _direction;
    update();
  }
  
  uint8_t DCMotorController::getDirection() {
    return direction;
  }

  void DCMotorController::update() {
    analogWrite(in1, direction ? pwm : 0);
    analogWrite(in2, direction ? 0 : pwm);
  }
};
