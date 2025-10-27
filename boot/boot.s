global loader
extern kernel_main

magic_nmb equ 0x1BADB002 
flags     equ 0x0
check     equ -(magic_nmb + flags)

section .text

align 4

    dd magic_nmb
    dd flags
    dd check

loader:
    mov eax, 0xCAFEBABE  ; Debug (opcional)

    call kernel_main     ; Chama o kernel principal em C

.loop:
    jmp .loop
