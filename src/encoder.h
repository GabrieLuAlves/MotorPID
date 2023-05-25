#ifndef ENCODER_H
#define ENCODER_H


class Encoder {
public:
  Encoder(uint8_t _pin, uint16_t pulsesPerTurn);
  void measureFrequency();
  double getFrequency();
  
private:
  uint8_t pin;
  double frequency = 0;
  double k;
};

#endif
