#include "Arduino.h"
#include "motor.h"


Motor::Motor(byte ENA, byte IN1, byte IN2) {
  this->ENA = ENA;
  this->IN1 = IN1;
  this->IN2 = IN2;
}

void Motor::setSpeed(float rpm) {
  analogWrite(ENA, floor(rpm) * 255 / 300);
}

void Motor::setDirection(Direction direction) {
  switch(direction) {
    case FORWARD:
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      break;
    case BACKWARDS:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      break;
    case STOP:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      break;
  }
}

void Motor::setPwm(byte pwm) {
  this->pwm = pwm;
  analogWrite(ENA, pwm);
}

byte Motor::getPwm() {
  return pwm;
}
