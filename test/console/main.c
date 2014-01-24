


#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"


int main( int argc, const char* argv[] )
{

    CON_init(30,15);

    int x = 0;
    int y = 0;
    while(1){
           CON_clearBuffer();
            CON_writeChar('x',x,x,0,CONSOLECOLOR_CYAN,CONSOLECOLOR_BLACK);
            CON_writeChar('x',x+1,x+1,0,CONSOLECOLOR_GREEN,CONSOLECOLOR_BLACK);
            CON_writeChar('x',x+2,x+2,0,CONSOLECOLOR_PURPLE,CONSOLECOLOR_BLACK);
             CON_writeChar('x',15-x,x+2,0,CONSOLECOLOR_RED,CONSOLECOLOR_BLACK);
            CON_writeChar('x',14-x,x+2,0,CONSOLECOLOR_RED,CONSOLECOLOR_BLACK);
            CON_writeChar('x',13-x,x+2,0,CONSOLECOLOR_RED,CONSOLECOLOR_BLACK);

            CON_writeText("Konsolentest Windows\0",1,1,CONSOLECOLOR_YELLOW,CONSOLECOLOR_BLACK,0,0);
            CON_writeText("Text in Weiß",1,2,CONSOLECOLOR_WHITE,CONSOLECOLOR_BLACK,0,0);
            CON_clearScreen();
            CON_flushBuffer();

            Sleep(150);
    if(x > 10){
        x = 0;
    }
    x++;

    }



    printf("Hello world!\n");
    return 0;
}

