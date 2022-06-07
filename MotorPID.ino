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

Encoder encoder(210);
PID pid(3.5, 0.75, 0, 60, 300, 0);
Motor motor(ENA, IN1, IN2);

void calculatePWM(void);
void displayValues(void);

void receive(short value) {
  if(value < 0) motor.setDirection(BACKWARD);
  else if(value > 0) motor.setDirection(FORWARD);
  else motor.setDirection(RELEASE);

  pid.setpoint = abs(value);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENCODER_PIN, INPUT);

  encoder.configure();
  
  motor.setDirection(FORWARD);

  spi.configure();

  spi.onTransferFinished(receive);
}

void loop() {
  calculatePWM();
  displayValues();
}

void calculatePWM(void) {
  rpm = encoder.measureRpm(50);
  pwm = floor(pid.calculatePID(rpm) * 255.0/ 300.0);
  motor.setPwm(pwm);
}

void displayValues(void) {
  Serial.print(rpm);
  Serial.print('\t');
  Serial.print(pid.setpoint);
  Serial.print('\t');
  Serial.print(pwm);
  Serial.print('\t');

  Serial.println();
}
