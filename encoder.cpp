#include "Arduino.h"
#include "encoder.h"

volatile double Encoder::frequency = 0;
volatile long unsigned Encoder::t = 0;
volatile long unsigned Encoder::t0 = 0;

Encoder::Encoder(short togglesPerRotation) {
  this->togglesPerRotation = togglesPerRotation;

  attachInterrupt(digitalPinToInterrupt(2), Encoder::onToggle, CHANGE);
}

inline void Encoder::onToggle() {
  Encoder::t = micros();
  
  Encoder::frequency =
    0.6 * (1000000 / (float(Encoder::t - Encoder::t0) * 420)) +
    0.4 * Encoder::frequency;
  
  Encoder::t0 = t;
}

float Encoder::getRpm() {
  if(micros() - Encoder::t0 > 50000) Encoder::frequency = 0.4 * Encoder::frequency;
  
  return Encoder::frequency * 60;
}
