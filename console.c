#include "console.h"

#define GET_2D_INDEX(x, y) (x + y * width)
#define BUFFER_CONTROLCHAR_FACTOR 64

int TE3D_Console_Init(int w, int h){

	//WinAPI Initialisierung

#ifdef WIN32

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE)
	{
		return -1;
	}

#endif
	

	// Create the buffer for the console and set it as new one.
	ConsoleBuffer = (char*)malloc(sizeof(char) * w * h * BUFFER_CONTROLCHAR_FACTOR);

	if(ConsoleBuffer == NULL)
		return -1;
	
	stream = stdout;
	setvbuf(stream, ConsoleBuffer, _IOFBF, sizeof(char) * w * h * BUFFER_CONTROLCHAR_FACTOR);

	// Clear the screen for the view.
	TE3D_Console_ClearScreen();
	TE3D_Console_ResetPosition();

	width = w;
	height = h;

	// At least hide the cursor.
	TE3D_Console_HideCursor();

	return 0;
}

int TE3D_Console_Close(){
	
	// Make the cursor visible.
	TE3D_Console_ShowCursor();

	// And additionally set the cursor at the end:
	TE3D_Console_SetPosition(0, width);

	TE3D_Console_FlushBuffer();
		
	// Reset buffer.
	setvbuf(stream, (char*)malloc(BUFSIZ), _IOLBF, BUFSIZ);
	ConsoleBuffer = NULL;

	stream = NULL;

	return 0;
}

int TE3D_Console_FlushBuffer(){

	fflush(stream);
	return 0;
}

/* Not supported
int CON_writeChar(char data,int posX, int posY, enum ConsoleColor fg,enum ConsoleColor bg){
	if(posX > width || posY > height){
		return -1;
	}

	int pos = GET_2D_INDEX(posX, posY);

	ConsoleBuffer[pos].bgColor = bg;
	ConsoleBuffer[pos].fgColor = fg;;
	ConsoleBuffer[pos].Char = data;
	
	return 0;

}*/

/* Not supported
int CON_writeText(char *text, int posX, int posY,enum ConsoleColor fg,enum ConsoleColor bg, int wrap){
	int pos = GET_2D_INDEX(posX, posY);

	while(*text != 0){
		ConsoleBuffer[pos].Char = *text;
		ConsoleBuffer[pos].fgColor = fg;
		ConsoleBuffer[pos].bgColor = bg;
		text++;
		pos++;
	}

	return 0;
} */


int TE3D_Console_SetPosition(int x, int y){

	#ifdef WIN32
		//ConsoleCoords.X = x;
		//ConsoleCoords.Y = y;
		COORD newcoords;
		newcoords.X = x;
		newcoords.Y = y;
		SetConsoleCursorPosition(hConsole, newcoords);
	#endif // WIN32

	#ifdef LINUX
		fprintf(stream, "\033[%d;%dH", y, x);
	#endif

	return 0;

}
int TE3D_Console_SetCurrentColor(enum ConsoleColor fg, enum ConsoleColor bg){

	#ifdef WIN32 //Operating system is Windows32

		if(fg == 0){
			SetConsoleTextAttribute(hConsole, WINCOLOR(DarkGray,Black));
		}else{
			SetConsoleTextAttribute(hConsole, WINCOLOR(ConsoleColorTableWin[fg-1],ConsoleColorTableWin[bg-1]));
		}

	#endif

	#ifdef LINUX //Operating system is LINUX/UNIX

		// Reset attributes.
		fputs("\033[0m", stream);

		if (bg != CONSOLECOLOR_DEFAULT)
		{
			
			fputs("\033[", stream);
			fputs(ConsoleColorTableLinuxBack[bg - 1], stream);
			putchar('m');
		}
		if(fg != CONSOLECOLOR_DEFAULT)
		{
			//Write Color to the Terminal
			fputs("\033[", stream);
			fputs(ConsoleColorTableLinuxFore[fg - 1], stream);
			putc('m', stream);
		}

	#endif

	return 0;
}



int TE3D_Console_ClearScreen(){

	#ifdef WIN32
		system("CLS");
	#endif

	#ifdef LINUX
		fputs("\033[2J", stream);
	#endif

	return 0;
}





char* TE3D_Console_GetBuffer(){
	return ConsoleBuffer;
}


// Moves the cursor of the console.
int TE3D_Console_MoveCursor(int x, int y)
{

#ifdef WIN32
	PCONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, info);
	COORD newcoord = info->dwCursorPosition;
	newcoord.X += x;
	newcoord.Y += y;
	SetConsoleCursorPosition(hConsole, newcoord);
#endif

#ifdef LINUX
	fprintf(stream, "\033[%dA\033[%dC", x, y);
	fflush(stream);
#endif

	return 0;

}

int TE3D_Console_NewLine()
{
	return putc('\n', stream);
}


int TE3D_Console_ResetPosition()
{
	return TE3D_Console_SetPosition(0,0);
}

FILE* TE3D_Console_GetStream()
{
	return stream;
}

int TE3D_Console_WriteChar(char chr)
{
	return putc(chr, stream);
}

int TE3D_Console_HideCursor()
{
	return fputs("\033[?1c", stream);
}

int TE3D_Console_ShowCursor()
{
	return fputs("\033[?0c", stream);
}