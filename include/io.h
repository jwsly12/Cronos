#ifndef IO_H
#define IO_H

#include <stdint.h>

//Arquivo io.h

void outb(uint16_t port, uint8_t signal);
uint8_t inb(uint16_t port);

#endif
