[BITS 32]
extern keyboard_handler
global keyboard_isr
global idt_load

keyboard_isr:
    pusha                ; Salva EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI
    
    mov ax, ds           ; Salva o segmento de dados atual
    push eax             

    mov ax, 0x10         ; Força o segmento de dados do Kernel (Padrão Multiboot)
    mov ds, ax
    mov es, ax

    call keyboard_handler ; Chama seu código C

    pop eax              ; Restaura o segmento de dados original
    mov ds, ax
    mov es, ax

    popa                 ; Restaura todos os registradores
    iretd                ; Retorno de 32-bits

idt_load:
    mov eax, [esp + 4]   ; Pega o ponteiro da struct idtp
    lidt [eax]           ; Carrega a IDT
    ret