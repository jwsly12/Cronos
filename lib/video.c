/*
Endereço Modo texto VGA: 0xB8000

int pos = 2 * (y * 80 + x); --> Posição

função print_screen(unsigned char color , char character , int x , int y )

unsigned char color: Cor
char character: String / caractérie a ser imprimido 
int x: posição eixo x
int y: posição eixo y 

*/

#include "../include/video.h"

//Função para printar na tela
void clear_screen(unsigned char color) {
    volatile char* video = (volatile char*)0xB8000;
    int screen_size = 80 * 25;

    for (int i = 0; i < screen_size; i++) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = color;
    }
}


void print_screen(unsigned char color, const char* string, int x, int y) {
    volatile char* video = (volatile char*)0xB8000;
    int width = 80;

    for (int i = 0; string[i] != '\0'; i++) {
        int pos = 2 * (y * width + (x + i));
        video[pos] = string[i];
        video[pos + 1] = color;
    }
}