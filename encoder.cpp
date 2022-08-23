#include "Arduino.h"
#include "encoder.h"

#define LAST_READINGS_ARRAY_SIZE 1

float filter = 1;
float measure = 1;

Encoder::Encoder(short togglesPerRotation) {
  this->togglesPerRotation = togglesPerRotation;

  TCCR1A = 0 << COM1A1 | 0 << COM1A0 | 0 << COM1B1 | 0 << COM1B0 | 0 << WGM11 | 0 << WGM10;
  TCCR1B = 0 << ICNC1 | 0 << ICES1 | 0 << WGM13 | 1 << WGM12 | 1 << CS12 | 1 << CS11 | 1 << CS10;
  TIMSK1 = 0 << OCIE1B | 0 << OCIE1A | 0 << TOIE1;
  TCNT1 = 0;
}

float Encoder::measureRpm() {
  bool timeout = false;
  unsigned t = 0, t0 = 0;
  
  unsigned timeoutCounter = 0;
  byte state = digitalRead(5);
  for(timeoutCounter = 40000 ; timeoutCounter && digitalRead(5) == state ; timeoutCounter--);
  if(timeoutCounter == 0) timeout = true;

  t0 = micros();

  state = !state;
  for(timeoutCounter = 40000 ; timeoutCounter && digitalRead(5) == state ; timeoutCounter--);
  if(timeoutCounter == 0) timeout = true;

  t = micros();
  
  if(timeout) measure = 0;
  else measure = 1000000.0 / (float(t - t0) * 420.0) * 60.0;
  
  filter = 0.2 * measure + 0.8 * filter;

  return filter;
}
