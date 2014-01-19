#include "console.h"

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
		COI_setColor((enum ConsoleColor)ConsoleBuffer[i].fgColor, (enum ConsoleColor)ConsoleBuffer[i].bgColor);
		putchar(ConsoleBuffer[i].Char);

		if(((i+1) % width == 0) && (i!= 0)){
			putchar('\n');
		}
	}
	return 1;
}

extern int CON_writeChar(char data,int posX, int posY, int layer, enum ConsoleColor fg,enum ConsoleColor bg){
	int pos = COI_getElementNumber(posX,posY);

	if(ConsoleBuffer[pos].layer >= layer ){
        ConsoleBuffer[pos].bgColor = bg;
        ConsoleBuffer[pos].fgColor = fg;;
        ConsoleBuffer[pos].Char = data;
        ConsoleBuffer[pos].layer = layer;
	}
    return 1;

}



int COI_setPosition(int x,int y){
	#ifdef WIN32
		ConsoleCoords.X = x;
		ConsoleCoords.Y = y;
		SetConsoleCursorPosition(hConsole,ConsoleCoords);
	#endif // WIN32


    return 1;

}


static int COI_setColor(enum ConsoleColor fg,enum ConsoleColor bg){

	#ifdef WIN32 //Operationssystem is Windows32

		if(fg == 0){
            SetConsoleTextAttribute(hConsole, WINCOLOR(DarkGray,Black));
		}else{
            SetConsoleTextAttribute(hConsole, WINCOLOR(ConsoleColorTableWin[fg-1],ConsoleColorTableWin[bg-1]));
		}



	#endif
	#ifdef LINUX //Operationsystem is LINUX/UNIX


        if(fg == 0){
            //Default color wished, clear Colorsetting
            puts("\033[0m");
        }else{
            //Write Color to the Terminal
            puts("\033[");
            puts(ConsoleColorTableLinuxFore[fg-1]);
            puts("\033[");
            puts(ConsoleColorTableLinuxBack[bg-1]);
        }

	#endif





	return 1;
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


extern  struct ConsoleCharacterInformation* getBuffer(){
    return ConsoleBuffer;
}


extern int CON_writeLine(int posX1,int posY1,int posX2,int posY2,int layer, enum ConsoleColor fg, enum ConsoleColor bg){
/*
    char lineElements[6] = {"-----"};

    //den Winkel der Linie berechnen
    float angle = (posY2 - posY1)/(posX2-posX1);


    int startX = 0;
    int startY = 0;

    if(posX1 > posX2){



    }

*/
    return 0;




}


int con_init(int width, int high){

#ifdef WIN32
	//WinAPI Initialisierung
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

#endif

    ConsoleBuffer = malloc(sizeof(struct ConsoleCharacterInformation));


return 1;
}




