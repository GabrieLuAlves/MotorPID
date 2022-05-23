#ifndef ENCODER_H
#define ENCODER_H


class Encoder {
public:
  Encoder(byte);
  
  void configure();
  
  float measureRpm(unsigned);
private:
  byte signalsPerRotation;
};

#endif
