#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include "Arduino.h"

class SPISlave{
public:
  void configure() const;
  void onTransferFinished(void (*)(short)) const;
};

extern const SPISlave spi;

#endif
