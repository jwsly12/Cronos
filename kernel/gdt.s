global gdt_flush

gdt_flush:
    mov eax, [esp + 4]  ; Pega o ponteiro da GDT
    lgdt [eax]          ; Carrega a nova GDT

    mov ax, 0x10        ; 0x10 é o seletor para o segmento de dados (2º entrada, 2 * 8)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush     ; Salto longe (far jump) para carregar o novo CS (0x08)

.flush:
    ret