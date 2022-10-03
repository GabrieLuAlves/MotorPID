#ifndef ENCODER_H
#define ENCODER_H


class Encoder {
public:
  Encoder(short);
  
  float getRpm();
private:
  static inline void onToggle();
  
  byte togglesPerRotation;
  static volatile double frequency;
  static volatile long unsigned t, t0;
};

#endif
