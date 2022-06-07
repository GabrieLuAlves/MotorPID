#include "spi_slave.h"

const SPISlave spi;

short rx = 0;
byte *pos = (byte*)&rx;
static void (*transferReceivedHandler)(short);


void SPISlave::configure() const {
  SPCR = 1 << SPIE | 1 << SPE; 
}

void SPISlave::onTransferFinished(void (*newFunction)(short)) const {
  transferReceivedHandler = newFunction;
}

ISR(SPI_STC_vect) {
  *(pos++) = SPDR;
  if(pos - (byte*)&rx >= 2) {
    transferReceivedHandler(rx);
    rx = 0;
    pos = (byte*)&rx;  
  }
}
