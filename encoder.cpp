#include "Arduino.h"
#include "encoder.h"


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
  unsigned x = 20;
  byte count = 0;
  while(digitalRead(5) && x--);
  TCNT1 = 0;
  delay(timeSpan);

  count = TCNT1;
  
  return float(count) / float(this->signalsPerRotation) / (timeSpan / 1000.0) * 60;
}
