#include "encoder.h"
#include "PID.h"
#include "motor.h"
#include "spi_slave.h"

#define ENA 3
#define IN1 4
#define IN2 2
#define MEASURE_PERIOD 200.0
#define ENCODER_PIN 5

float rpm = 0;
unsigned pwm = 0;

Encoder encoder(420);
// PID pid(5.93359375, 0.49951171, 0, 60, 255, 0);
PID pid(5.93359375, 0.49951171, 0, 60, 255, 0);

Motor motor(ENA, IN1, IN2);

void displayValues(void);

void receive(short value) {
  if(value < 0) motor.setDirection(BACKWARD);
  else if(value > 0) motor.setDirection(FORWARD);
  else motor.setDirection(RELEASE);

  pid.setpoint = abs(value);
}

void setup() {
  Serial.begin(2000000);
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENCODER_PIN, INPUT);
  
  motor.setDirection(FORWARD);

  spi.configure();

  spi.onTransferFinished(receive);
}

void loop() {/*
  pid.kp = analogRead(A0) / 1024.0 * 4 + 4;
  pid.ki = analogRead(A1) / 1024.0 * 0.5;*/
 
  rpm = encoder.measureRpm();
  pwm = floor(pid.calculatePID(rpm));
  motor.setPwm(pwm);
  
  // displayValues();
}

static unsigned x = 0;

void displayValues(void) {
  Serial.print(rpm);
  Serial.print('\t');
  Serial.print(pwm);
  Serial.print('\t');
  Serial.println(micros());
}
