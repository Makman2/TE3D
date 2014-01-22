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
		ConsoleBuffer[i].bgColor = CONSOLECOLOR_DEFAULT;
		ConsoleBuffer[i].fgColor = CONSOLECOLOR_DEFAULT;
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

#ifdef LINUX
	// Save cursor position.
	fputs("\033[s", stdout);
#endif

	for(int i = 0;i<z;i++){
		COI_setColor((enum ConsoleColor)ConsoleBuffer[i].fgColor, (enum ConsoleColor)ConsoleBuffer[i].bgColor);
		putchar(ConsoleBuffer[i].Char);

		if(((i+1) % width == 0) && (i!= 0)){
			putchar('\n');
		}
	}

#ifdef LINUX
	// Restore cursor position.
	fputs("\033[u", stdout);
#endif

	return 1;
}

int CON_writeChar(char data,int posX, int posY, int layer, enum ConsoleColor fg,enum ConsoleColor bg){
	if(posX > width || posY > hight){
		return 0;
	}

	int pos = COI_getElementNumber(posY,posX);

	if(ConsoleBuffer[pos].layer >= layer ){
		ConsoleBuffer[pos].bgColor = bg;
		ConsoleBuffer[pos].fgColor = fg;;
		ConsoleBuffer[pos].Char = data;
		ConsoleBuffer[pos].layer = layer;
	}
	return 1;

}
int CON_writeText(char *text, int posX, int posY,enum ConsoleColor fg,enum ConsoleColor bg, int layer,int wrap){
	int pos = COI_getElementNumber(posY,posX);

	while(*text != 0){
		ConsoleBuffer[pos].Char = *text;
		ConsoleBuffer[pos].fgColor = fg;
		ConsoleBuffer[pos].bgColor = bg;
		ConsoleBuffer[pos].layer = layer;
		text++;
		pos++;
	}

	return 1;
}


static int COI_setPosition(int x,int y){
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

		// Reset attributes.
		fputs("\033[0m", stdout);
		if(fg != CONSOLECOLOR_DEFAULT)
		{
			//Write Color to the Terminal
			fputs("\033[", stdout);
			fputs(ConsoleColorTableLinuxFore[fg - 1], stdout);
			putchar('m');
		}

		if (bg != CONSOLECOLOR_DEFAULT)
		{
			fputs("\033[", stdout);
			fputs(ConsoleColorTableLinuxBack[bg - 1], stdout);
			putchar('m');
		}

	#endif

	return 1;
}


static int COI_clearScreen(){

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





extern  struct ConsoleCharacterInformation* getBuffer(){
	return ConsoleBuffer;
}






