#include "../include/video.h"


//void logo(void); 

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


void kernel_main() {
 
    logo();
    while (1) {}
}
