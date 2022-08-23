#ifndef ENCODER_H
#define ENCODER_H


class Encoder {
public:
  Encoder(short);
  
  float measureRpm();
private:
  byte togglesPerRotation;
};

#endif
