/*
copied from GazOS Operating System
*/

#ifndef CORE_DMA_H
#define CORE_DMA_H

void dma_xfer(unsigned char channel, unsigned long address, unsigned int length, unsigned char read);

#endif
