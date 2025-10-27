ENTRY(loader) /* o nome do rótulo de entrada */
SECTIONS {
. = 0x00100000; /* o código deve ser carregado em 1 MB */
.text ALIGN (0x1000) :
{
*(.text)
}
/* alinhado em 4 KB */
/* todas as seções de texto de todos os arquivos */
.rodata ALIGN (0x1000) : /* alinhado em 4 KB */
{
*(.rodata*)
/* todas as seções de dados somente leitura de todos os arquivos */
}
.data ALIGN (0x1000) :
{
*(.data)
} /* alinhado em 4 KB */
.bss ALIGN (0x1000) :
{
*(COMMON)
*(.bss)
} /* alinhado em 4 KB */
/* todas as seções de dados de todos os arquivos */
/* todas as seções COMMON de todos os arquivos */
/* todas as seções bss de todos os arquivos */
}
