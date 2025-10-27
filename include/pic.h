#ifndef _PIC_H_
#define _PIC_H_

// Inicializa e remapeia o PIC
void pic_remap();

// Envia EOI (End of Interrupt) para o PIC apropriado
void pic_send_eoi(unsigned char irq);

// Ativa (desmascara) uma linha IRQ
void pic_clear_mask(unsigned char irq_line);

// Desativa (mascara) uma linha IRQ
void pic_set_mask(unsigned char irq_line);

#endif // _PIC_H_
