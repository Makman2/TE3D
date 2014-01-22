/*

Console.h
Version 1.0
08.01.2014




Enthält alle Funktionen welche zur Darstellung der Daten in der Konsole nötig sind

Hinweise:
Unter Windows wird die zuletzt gewählte Zeichenhintergrundfarbe zur GesamtHintergrundfarbe übernommen.

Änderungen:
	- Fehler entfernt
	- direkter Zugriff auf den Buffer nötig (muss noch getestet werden! kann sein das es linkerfehler hervorruft)
	-Layer definiert
	-Funktion CON_writeChar (vorher CON_setCharacter) umbenannt
	- Ausgabe unter Linux implementierrt (Muss noch getestet werden!)
	- Auf den Konsolenspeicher sollte (demnächst) nicht mehr direkt zugegriffen werden, da ich an der Strucktur etwas ändern werde!
	- Layer werden abgefragt

Noch zu tun:
	- implementierung der Verwendung der Cursorposition (Win+Unix)
	- Farbige Ausgabe Linux

	- Schreiben eines Textes in die Konsole


Momentaner Stand:

	- unter anderen Betriebssystemen ist die Ausgabe noch nicht implementiert, es ist jedoch eine Schwarzweiß Ausgabe schon möglich





###########################################################################################

Copyright (C) 2014 Mischa Krüger, Ammar Al-Qaiser, Frank Zimdars, Gordon Kemsies

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once


#include <stdio.h>
#include <stdlib.h>



#ifdef WIN32
	#include <windows.h>
	#define WINCOLOR(a,b) (b<<4)+a //Build the Win-Terminal Color, A = Foreground B= Background
#endif


#define CON_DEFAULT_SIZE_X_WIN      79
#define CON_DEFAULT_SIZE_Y_WIN      25
#define CON_DEFAULT_SIZE_X_LINUX    0
#define CON_DEFAULT_SIZE_Y_LINUX    0


#define CON_DRAWMODE_FULL
#define CON_DRAWMODE_SELECT


#define CON_LAYER_BOTTOM 0
#define CON_LAYER_TOP    256


#define CONSOLECOLOR_DEFAULT (enum ConsoleColor)0
#define CONSOLECOLOR_BLACK (enum ConsoleColor)1
#define CONSOLECOLOR_WHITE (enum ConsoleColor)2
#define CONSOLECOLOR_BLUE (enum ConsoleColor)3
#define CONSOLECOLOR_GREEN (enum ConsoleColor)4
#define CONSOLECOLOR_RED (enum ConsoleColor)5
#define CONSOLECOLOR_YELLOW (enum ConsoleColor)6
#define CONSOLECOLOR_CYAN (enum ConsoleColor)7
#define CONSOLECOLOR_MAGENTA (enum ConsoleColor)8
#define CONSOLECOLOR_PURPLE (enum ConsoleColor)9
#define CONSOLECOLOR_DARKGRAY (enum ConsoleColor)10
#define CONSOLECOLOR_BROWN (enum ConsoleColor)11

//Die erweiterten Plattformabhängigenfarben sind momentan auskommentiert, damit durch die Benutzung dieser keine Probleme
//hervorgerufen werden
/*
#ifdef LINUX
	#define CONSOLECOLOR_LIGHTBLUE (enum ConsoleColor)11
	#define CONSOLECOLOR_LIGHTGREEN (enum ConsoleColor)12
	#define CONSOLECOLOR_LIGHTCYAN (enum ConsoleColor)13
	#define CONSOLECOLOR_LIGHTRED (enum ConsoleColor)14
	#define CONSOLECOLOR_LIGHTPURPLE (enum ConsoleColor)15
#endif
#ifdef WIN32
	#define CONSOLECOLOR_DARKBLUE (enum ConsoleColor)11
	#define CONSOLECOLOR_DARKGREEN (enum ConsoleColor)12
	#define CONSOLECOLOR_BLUEGREEN (enum ConsoleColor)13
	#define CONSOLECOLOR_DARKRED (enum ConsoleColor)14
#endif
*/



enum ConsoleColor{

	//Für alle Systeme verfügbar
	Default  = 0,
	Black = 1,
	White = 2,
	Blue = 3,
	Green = 4,
	Red = 5,
	Yellow = 6,
	Cyan = 7,
	Magenta = 8,
	Purple = 9,
	DarkGray = 10,
	Brown = 11,
/*
#ifdef LINUX
	//Only avaiable under Unix
	LightBlue = 12,
	LightGreen = 13,
	LightCyan = 14,
	LightRed = 15,
	LightPurple = 16
#endif

#ifdef WIN32
	//Only avaiable under Windows (Win32)
	DarkBlue = 12,
	DarkGreen = 13,
	BlueGreen = 14,
	DarkRed = 15
#endif
*/
};




struct ConsoleCharacterInformation{
	char Char;
	int bgColor;
	int fgColor;
	int layer;
};

struct ConsoleDrawOperation{
	int x;
	int y;
	struct ConsoleCharacterInformation data;
	struct ConsoleDrawOperation *next;
};




//Private Functions
//

static int      COI_setPosition(int x,int y);
static int      COI_setColor(enum ConsoleColor fg,enum ConsoleColor bg);
static int      COI_getElementNumber(int x,int y);



static struct   ConsoleCharacterInformation *ConsoleBuffer;
static int      height, width;


static struct ConsoleDrawOperation *ConsoleOperationBuffer;

#ifdef WIN32
	static HANDLE   hConsole;
	static COORD    ConsoleCoords;
	static int      ConsoleColorTableWin[] = { 0x00, 0x0F, 0x09, 0x0A, 0x0C, 0x0E, 0x0B, 0x0D, 0x05, 0x08, 0x06 };

#endif
#ifdef LINUX
	static char     ConsoleColorTableLinuxFore[][5] = {"0;30","1;37","0;34","0;32","0;31","1;33","0;36","1;35","0;35","1;30","0;33"};
	static char     ConsoleColorTableLinuxBack[][5] = {"0;40","1;47","0;44","0;42","0;41","1;43","0;46","1;45","0;45","1;40","0;43"};

#endif


//Public functions


//Writes a string in the ConsoleBuffer
extern int CON_writeText(char *text, int posX, int posY,enum ConsoleColor fg,enum ConsoleColor bg, int layer,int wrap);
//Writes a char in the ConsoleBuffer
extern int CON_writeChar(char data,int posX, int posY, int layer, enum ConsoleColor fg,enum ConsoleColor bg);
//Write a Line of Chars in the Buffer
extern int CON_writeLine(int posX1,int posY1,int posX2,int posY2,int layer, enum ConsoleColor fg, enum ConsoleColor bg);





//Clears the Console
extern int CON_clearScreen();
//Reset the ConsoleBuffer
extern int CON_clearBuffer();
//Init the ConsoleBuffer
extern int CON_init(int w,int h);
//Close the Module
extern int CON_close();
//Print the consoleBuffer out to the Console
extern int CON_flushBuffer();

// Moves the cursor of the console.
// x: The x-steps to move.
// y: The y-steps to move.
int CON_moveCursor(int x, int y);

extern struct ConsoleCharacterInformation* CON_getBuffer();






