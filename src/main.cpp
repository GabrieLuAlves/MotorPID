#include <Arduino.h>

#include <Wire.h>

#include "PID.h"
#include "Encoder.h"
#include "L298N_DCMotorController.h"

L298N::DCMotorController motor1(06, 05, 300);
L298N::DCMotorController motor2(11, 10, 300);

PID pid1(5, 0, 0.0, 60);
PID pid2(5, 0, 0.0, 60);

Encoder encoder1(2, 420);
Encoder encoder2(3, 420);

void handle(int bytes) {
  noInterrupts();
  
  if (bytes == 4) {
    int16_t temp_motor1_target = 0;
    int16_t temp_motor2_target = 0;

    temp_motor1_target |= Wire.read(); temp_motor1_target <<= 8;
    temp_motor1_target |= Wire.read();

    temp_motor2_target |= Wire.read(); temp_motor2_target <<= 8;
    temp_motor2_target |= Wire.read();

    pid1.setSetpoint((double)temp_motor1_target);
    pid2.setSetpoint((double)temp_motor2_target);
  }

  interrupts();
}

void setup() {
  Serial.begin(9600);
  
  Wire.begin(0x23);
  Wire.onReceive(handle);

  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  motor1.setDirection(FORWARD);
  motor2.setDirection(FORWARD);
}

void loop() {
  double control;
  uint8_t pwm;

  encoder1.measureFrequency();
  control = pid1.calculate(encoder1.getFrequency());
  if (control > 300) control = 300;
  pwm =  ceil(control / 300 * 255);
  motor1.setPwm(pwm);

  encoder2.measureFrequency();
  control = pid2.calculate(encoder1.getFrequency());
  if (control > 300) control = 300;
  pwm =  ceil(control / 300 * 255);
  motor2.setPwm(pwm);
}