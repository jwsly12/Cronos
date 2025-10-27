#include "../include/pic.h"
#include "../include/io.h"

// Endereços das portas do PIC mestre e escravo
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

// Comandos de inicialização (ICWs)
#define ICW1_INIT  0x11  // Inicia a configuração
#define ICW4_8086  0x01  // Modo 8086/88


/*

O PIC é o controlador de Interrupções programável

Ele serve para dizer ao processador quem pode o 
interromper quando necessário.

Funções

pic_send_eio : Envia o comando EOI 
(End of Interrupt) para o(s) PIC(s) 
para informar que o processador 
terminou de tratar a interrupção.

Use para liberar o processador para novas interrupções

pic_set_mask : Desativa (mascara) a interrupção 
de uma linha IRQ específica.Isso impede que o 
PIC aceite interrupções daquele dispositivo.

Use quando quiser bloqueiar um dispositivo para que ele
não interrompa

pic_clear_mask : Ativa (desmascara) a interrupção 
de uma linha IRQ específica.Permite que o 
dispositivo envie interrupções ao processador.

Use quando quiser que um dispositvo interrompa

Lembre-se que ao programar um sistema o assincronismo é mais
do que importante:

"Não bloqueie o processador esperando algo lento 
(como disco, teclado, rede...). Em vez disso, 
continue rodando outras coisas e só volte 
quando o dispositivo disser: “estou pronto”

*/

//Arquivo pic.c

void pic_remap() {
  unsigned char a1 = inb(PIC1_DATA);
  unsigned char a2 = inb(PIC2_DATA);

 //Inicialização de ambos os PICs
  outb(PIC1_COMMAND , ICW1_INIT);
  outb(PIC2_COMMAND , ICW1_INIT);

  outb(PIC1_DATA , 0x20);
  outb(PIC2_DATA , 0x28);

  outb(PIC1_DATA , 0x04);
  outb(PIC2_DATA , 0x02);

  outb(PIC1_DATA , ICW4_8086);
  outb(PIC2_DATA , ICW4_8086);

  outb(PIC1_DATA , a1);
  outb(PIC2_DATA , a2);

}


pic_send_eio(unsigned char irq) {
 
    if(irq >= 8 ){
        outb(PIC2_COMMAND , 0x20);
    }
    outb(PIC1_COMMAND , 0x20);
}

void  pic_set_mask(unsigned chat irq_line){

    unsigned short port;
    unsigned char value;

    if(irq_line < 8 ){
        port = PIC1_DATA;
    }else{
         port = PIC2_DATA;
         irq_line -= 8;
    }
    value = inb(port) | (1 << irq_line);
    outb(port , value);

}

void pic_clear_mask(unsigned char irq_line) {
    unsigned short port;
    unsigned char value;

    if (irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = inb(port) & ~(1 << irq_line);
    outb(port, value);
}
