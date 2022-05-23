#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include "Arduino.h"

class SPISlave{
public:
  void configure();
  bool available();
  unsigned readUnsigned();
};

#endif
