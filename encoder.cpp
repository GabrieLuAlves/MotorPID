#include "Arduino.h"
#include "encoder.h"

#define LAST_READINGS_ARRAY_SIZE 1

float measure = 0;
float lastReadings[LAST_READINGS_ARRAY_SIZE];
unsigned index = 0;

Encoder::Encoder(byte signalsPerRotation) {
  this->signalsPerRotation = signalsPerRotation;
}

void Encoder::configure() {
  TCCR1A = 0 << COM1A1 | 0 << COM1A0 | 0 << COM1B1 | 0 << COM1B0 | 0 << WGM11 | 0 << WGM10;
  TCCR1B = 0 << ICNC1 | 0 << ICES1 | 0 << WGM13 | 1 << WGM12 | 1 << CS12 | 1 << CS11 | 1 << CS10;
  TIMSK1 = 0 << OCIE1B | 0 << OCIE1A | 0 << TOIE1;
  TCNT1 = 0;
}

float Encoder::measureRpm(unsigned timeSpan) {
  bool timeout = false;
  unsigned t = 0, t0 = 0;
  
  unsigned timeoutCounter = 0;
  byte state = digitalRead(5);
  for(timeoutCounter = 30000 ; timeoutCounter && digitalRead(5) == state ; timeoutCounter--);
  if(timeoutCounter == 0) timeout = true;

  t0 = micros();

  state = !state;
  for(timeoutCounter = 30000 ; timeoutCounter && digitalRead(5) == state ; timeoutCounter--);
  if(timeoutCounter == 0) timeout = true;

  t = micros();

  if(timeout) measure = 0;
  else measure = 0.1 * (1000000.0 / ((t - t0) * 420.0) * 60) + 0.9 * measure;

  /*
  lastReadings[index++] = measure;
  if(index >= LAST_READINGS_ARRAY_SIZE) lastReadings[index++] = 0;

  float sum = 0.0;
  for(unsigned i = 0 ; i < LAST_READINGS_ARRAY_SIZE ; i++) sum += lastReadings[i];
  
  return sum / LAST_READINGS_ARRAY_SIZE;
  */

  return measure;
}
