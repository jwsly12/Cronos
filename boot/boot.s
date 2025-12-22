[BITS 32]

global loader
extern kernel_main

; --- Cabeçalho Multiboot ---
magic_nmb equ 0x1BADB002 
flags     equ 0x0
check     equ -(magic_nmb + flags)

section .multiboot
align 4

    dd magic_nmb
    dd flags
    dd check

; --- Espaço para a Pilha (Stack) ---
section .bss
align 16
stack_bottom:
    resb 16384          ; 16 KB de pilha
stack_top:

; --- Código de Entrada ---
section .text
loader:
    mov esp, stack_top  ; Inicializa a pilha (O C precisa disso!)
    
    call kernel_main    ; Chama a função principal do seu kernel.c

.halt:
    hlt                 ; Para a CPU até a próxima interrupção
    jmp .halt