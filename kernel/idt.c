/*
A IDT (Interrupt Descriptor Table) é basicamente uma tabela que informa 
ao processador “quem deve tratar cada interrupção ou exceção”.

Hardware (timer, teclado, etc)
        │
        ▼
    PIC (Controlador de Interrupções)
        │
        ▼
    IDT (tabela que aponta para os ISRs)
        │
        ▼
    ISR (função do kernel que trata a interrupção)
        │
        ▼
    Retorno para o que a CPU estava fazendo


*/

/*
As entradas da IDT são as informações que o processador precisa
para executar um handler de uma interrupção.

base_low + base_high → sem isso, o CPU não sabe para qual função pular.
sel → define o segmento de código do kernel; sem isso, o CPU pode pular para memória errada.
always0 → deve ser zero; é exigência do formato da IDT.
flags → indica se a entrada está ativa (presente) e qual o tipo; sem isso, a interrupção não funcionará.

*/

//Entradas


#define IDT_ENTRIES 256
#include "../include/stdint.h"

struct idt_entry {

    unsigned short base_low;  //16 bits baixos da ISR
    unsigned short sel;       //Segmento do código do kernel
    unsigned char  always0;    //sempre em 0
    unsigned char  flags;      //Privilégios
    unsigned short base_high;   //16 bits altos da ISR
    
} __attribute__((packed));

//ponteiro
struct idt_pointer {

    unsigned short limit;
    unsigned int base;

} __attribute__((packed));

//Tabela de 256 entradas da IDT
struct idt_entry idt[IDT_ENTRIES];
struct idt_pointer idtp;

//Inicializar a tabela

/*
num → Número da entrada da IDT (0–255).
base → Endereço da função que vai tratar a interrupção (ISR).
sel → Seletor de segmento de código no GDT.
flags → Tipo da porta e nível de privilégio da interrupção.
*/

void idt_set_gate(int num, uint32_t  base, uint16_t  sel, uint8_t  flags){

    idt[num].base_low  = base & 0xFFFF;
    idt[num].sel       = sel;
    idt[num].always0   = 0;
    idt[num].flags     = flags;
    idt[num].base_high = (base >> 16) & 0xFFFF;

}


//Carregar a IDT

/*
r = registrado EAX
*/

static inline void load_idt(struct idt_pointer* idtp){
   __asm__ volatile ("lidtl (%0)" : : "r"(idtp));
/*
global idt_load
idt_load:
    lidt [eax]    ; Carrega o endereço passado em EAX
    ret

*/
}

//Inicializar IDT

void init_idt(){

    //Ponteiro
    idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES ) - 1;
    idtp.base  = (uint32_t)&idt;

    //Zera Tabela
    for (int i = 0 ; i < IDT_ENTRIES; i++ ){
        idt_set_gate(i ,0 ,0);
    }

    idt_load(&idtp)
}