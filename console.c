#include "console.h"



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
	//Zum Ändern der Farbe
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