#include "spi_slave.h"


byte buffer[254];
byte *p = buffer;

void SPISlave::configure() {
  SPCR = 1 << SPE | 1 << SPIE;
}

ISR(SPI_STC_vect) {
}
