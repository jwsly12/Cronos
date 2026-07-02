#include <stdint.h>
#include "../include/io.h"


/*
Arquivo: lib/io.c

outb (output byte): escreve um byte em uma porta I/O
inb (input byte): lê um byte de uma porta I/O

Para fazer essas funções precisamos fazer um manipulação de 
baixo nível usando assembly:

;Para outb

mov dx, 0x20      ; coloca o número da porta (PIC1_COMMAND) em DX
mov al, 0x11      ; coloca o valor (ICW1) em AL
outb al, dx       ; envia 0x11 para a porta 0x20

;Para inb

mov dx, 0x20    ; coloca o número da porta (ex: PIC1_COMMAND) em DX
inb al, dx      ; lê 1 byte da porta DX para o registrador AL


Podemos criar uma função inline assembly para fazer isso 

uint16_t :  DX  16 bytes Numero da PORTA de I/O
uint8_t  :  AL  8  bytes Valor a ser enviado e recebido

Esses vão ser os argumentos da função outb(Para inb apenas a porta)

"a" é a constraint que indica que o valor deve estar no registrador AL/AX/EAX dependendo do tamanho do dado.
"N" significa que o valor pode ser um imediato constante de 8 bits (0 a 255), que pode ser usado diretamente na instrução.
"d" significa que o valor deve estar no registrador DX (16 bits).

*/

//Apenas leitura

 void outb(uint16_t port , uint8_t signal ) {
 
     __asm__ volatile ("outb %0 , %1" : : "a"(signal) , "Nd"(port));
     /*
     mov dx, 0x20      ; coloca o número da porta (PIC1_COMMAND) em DX
     mov al, 0x11      ; coloca o valor (ICW1) em AL
     outb al, dx       ; envia 0x11 para a porta 0x20
     */

}

 uint8_t inb(uint16_t port){

    uint8_t ret; //Aloca espaço para AL
    __asm__ volatile ("inb %1 , %0" : "=a"(ret) : "Nd"(port));
    /*
    mov dx, 0x20    ; coloca o número da porta (ex: PIC1_COMMAND) em DX
    inb al, dx      ; lê 1 byte da porta DX para o registrador AL
    */
    return ret; //Retorna o valor do registrador AL
}

//Escrita
