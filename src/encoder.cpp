#include "Arduino.h"
#include "encoder.h"


Encoder::Encoder(uint8_t _pin, uint16_t pulsesPerTurn) : pin{_pin} {
  k = 1000000.0 / pulsesPerTurn * 60.0;
}

void Encoder::measureFrequency() {
  bool state = 0;
  int32_t dt = 0;
  uint32_t timeout;

  timeout = 7500;
  state = digitalRead(pin);
  while (digitalRead(pin) == state && --timeout);

  if (timeout == 0) {
    frequency = 0;
    return;
  }

  timeout = 7500;
  dt = micros();
  while(digitalRead(pin) != state && --timeout);
  dt = micros() - dt;

  if (timeout < 0) frequency = 0;
  else frequency = k / dt;
}

double Encoder::getFrequency() {
  return frequency;
}
