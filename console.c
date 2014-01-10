#include "console.h"

#include "console.h"

#pragma once

int CON_init(int w, int h){

	//WinAPI Initialisierung

	#ifdef WIN32
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	#endif // WIN32


	ConsoleBuffer = (struct ConsoleCharacterInformation*) malloc(sizeof(struct ConsoleCharacterInformation) * w * h);
	if(ConsoleBuffer == 0){
        return 0;
	}

	CON_clearBuffer();
    width = w;
    hight = h;


    return 1;
}
int CON_clearBuffer(){

    for(int i = 0;i< width * hight;i++){
        ConsoleBuffer[i].bgColor = Black;
        ConsoleBuffer[i].fgColor = White;
        ConsoleBuffer[i].layer = 0;
        ConsoleBuffer[i].Char = ' ';
        ConsoleBuffer[i].effect = normal;

    }
    return 1;
}
int CON_close(){
    free(ConsoleBuffer);
    return 1;
}

int CON_flushBuffer(){

    int z = width * hight;

    for(int i = 0;i<z;i++){
             COI_setColor(ConsoleBuffer[i].fgColor,ConsoleBuffer[i].bgColor,ConsoleBuffer[i].effect);
        putchar(ConsoleBuffer[i].Char);

        if(((i+1) % width == 0) && (i!= 0)){
            //
            //COI_setColor(White,Black,normal);

            putchar('\n');
        }
    }
}

extern int CON_setCharacter(char data,int posX, int posY, int layer, enum ConsoleColor fg,enum ConsoleColor bg,enum ConsoleEffect effect){
    int pos = COI_getElementNumber(posX,posY);
    ConsoleBuffer[pos].bgColor = bg;
    ConsoleBuffer[pos].fgColor = fg;
    ConsoleBuffer[pos].effect = effect;
    ConsoleBuffer[pos].Char = data;
    ConsoleBuffer[pos].layer = layer;

}




int COI_setColor(enum ConsoleColor fg,enum ConsoleColor bg,enum ConsoleEffect effect){

	#ifdef WIN32
        SetConsoleTextAttribute(hConsole, WINCOLOR(ConsoleColorTableWin[fg],ConsoleColorTableWin[bg]));

	#endif

    //puts("\033[");
    //char tmpBuf[5];
    //strcpy(tmpBuf,ConsoleColorTableLinux[fg]);



    return 1;
}
static int  COI_getElementNumber(int x,int y){
    return x*width + y;
}


 int CON_clearScreen(){

	#ifdef WIN32
		system("CLS");
	#endif

	#ifdef LINUX
		system("clear");
	#endif

	return 1;
}


#ifdef WIN32
	static HANDLE hConsole;
#endif






int con_init(int width, int high){


	//WinAPI Initialisierung
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	//ConsoleBuffer = malloc(sizeof(struct ConsoleCharacterInformation));
	
	
}
int COI_setColor(enum ConsoleColor fg,enum ConsoleColor bg){
	//Zum �ndern der Farbe
	SetConsoleTextAttribute(hConsole, 0x02);
}



 int COI_clearScreen(){
	
	#ifdef WIN32
		system("CLS");
	#endif
	#ifdef LINUX
		system("clear");
	#endif

	return 1;
}
