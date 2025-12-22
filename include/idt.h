#ifndef IDT_H
#define IDT_H

#include "stdint.h"

void init_idt();
void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);

#endif