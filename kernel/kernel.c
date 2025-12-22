#include "../include/video.h"
#include "../include/pic.h"
#include "../include/idt.h"
#include "../include/io.h"

int cursor_x = 0;
int cursor_y = 18;

extern void init_gdt();
void logo() {


    // Arte ASCII (9 linhas)
   const char *ascii_art[] = {
    " ____                                                   _____   ____       ",
    "/\\  _`\\                                               /\\  __`\\/\\  _`\\     ",
    "\\ \\ \\/\\_\\  _ __   ___     ___     ___     ____       \\ \\ \\/\\ \\ \\ \\L\\_\\   ",
    " \\ \\ \\/_/_/\\`'__\\/ __`\\ /' _ `\\  / __`\\  /',__\\       \\ \\ \\ \\ \\/_\\__ \\   ",
    "  \\ \\ \\L\\ \\ \\ \\//\\ \\L\\ \\/\\ \\/\\ \\/\\ \\L\\ \\/\\__, `\\       \\ \\ \\_\\ \\/\\ \\L\\ \\ ",
    "   \\ \\____/\\ \\_\\\\ \\____/\\ \\_\\ \\_\\ \\____/\\/\\____/        \\ \\_____\\ `\\____\\",
    "    \\/___/  \\/_/ \\/___/  \\/_/\\/_/\\/___/  \\/___/   _______\\/_____/\\/_____/ ",
    "                                                 /\\______/               ",
    "                                                 \\/______/               "
   };

    clear_screen(0x0A); // limpa a tela antes de exibir a logo

    for (int i = 0; i < 9; i++) {
        print_screen(0x0A, ascii_art[i], 0, i + 7);  // Centralizado verticalmente
    }

    print_screen(0xF , "By: wsly" , 4 , 15);
}


char *scancode_to_char[] = {
    "?", "?", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "BACK",
    "TAB", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "ENTER",
    "CTRL", "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "LSHIFT"
};



void keyboard_handler() {
    uint8_t scancode = inb(0x60); 

    // Verifica se a tecla foi PRESSIONADA (bit 7 desligado)
    if (!(scancode & 0x80)) {
        // Se for scancode de espaço (0x39) ou letras/números válidos
        if (scancode == 0x0E){
            if(cursor_x >0){
                cursor_x--;
                print_screen(0x0F , " " , cursor_x , cursor_y);
            }
        }
        else if (scancode < 58 && scancode_to_char[scancode][0] != '?') {
            
            char* tecla = scancode_to_char[scancode];
            
            // Tratamento especial para o ENTER
            if (scancode == 0x1C) {
                cursor_x = 0;
                cursor_y++;
            } else {
                print_screen(0x0F, tecla, cursor_x, cursor_y);
                cursor_x += 1; // Avança o cursor
            }

            // Scroll simples: se chegar no fim da linha
            if (cursor_x >= 80) {
                cursor_x = 0;
                cursor_y++;
            }
            
        }
    }

    pic_send_eoi(1);
}

void kernel_main() {
    init_gdt();   
    init_idt();   
    pic_remap();  

    logo();
    print_screen(0x0F, "Sistema pronto! Digite algo:", 0, 17);

    
    outb(0x21, 0xFD); 

    __asm__ volatile("sti");

    while (1) {
        __asm__ volatile("hlt");
    }
}
