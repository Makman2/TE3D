/*

Console.h
Version 1.0
08.01.2014




Enthält alle Funktionen welche zur Darstellung der Daten in der Konsole nötig sind

Hinweise:
Unter Windows wird die zuletzt gewählte Zeichenhintergrundfarbe zur GesamtHintergrundfarbe übernommen.


Noch zu tun:
    - implementierung der Verwendung der Cursorposition (Win+Unix)
    - Farbige Ausgabe Linux
    - Layer ermöglichen


Momentaner Stand:
    - Texteffekte entfernt, da nicht wirklich nötig
	- Farbige Ausgabe unter Windows möglich
	- unter anderen Betriebssystemen ist die Ausgabe noch nicht implementiert, es ist jedoch eine Schwarzweiß Ausgabe schon möglich
	- Texteffekte des Linuxterminals werden noch nicht unterstützt
	- Schreiben eines Textes in den Buffer noch nicht implementiert
	- Layer werden angenommen, jedoch noch nicht verglichen, der Text wird immer überschrieben

Verbindung mit dem Rest der Bibliothek über console_abstraction.h


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


#define WIN32

#pragma once

#include <stdio.h>
//#include "graphics.h"

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


enum ConsoleColor{

	//Für alle Systeme verfügbar
	Black,
	White,
	Blue,
	Green,
	Red,
	Yellow,
	Cyan,
	Magenta,
	Purple,
	DarkGray,
	Brown,
	//Spziell unter Linux verfügbar:
	LightBlue,
	LightGreen,
	LightCyan,
	LightRed,
	LightPurple,

	//Windows:
	DarkBlue,
	DarkGreen,
	BlueGreen,
	DarkRed,

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







//Public functions


//Writes a string in the ConsoleBuffer
extern int CON_writeText(char *text, int posX, int posY,int wrap);

//Writes a char in the ConsoleBuffer (deprecated)
#define CON_writeChar CON_setCharacter
extern int CON_setCharacter(char data,int posX, int posY, int layer, enum ConsoleColor fg,enum ConsoleColor bg);



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




//Private Functions
//

static int      COI_setPosition(int x,int y);
static int      COI_setColor(enum ConsoleColor fg,enum ConsoleColor bg);
static int      COI_getElementNumber(int x,int y);



static struct   ConsoleCharacterInformation *ConsoleBuffer;
static int      bufferSize = 0;
static int      hight, width;


#ifdef WIN32
	static HANDLE   hConsole;
	static COORD    ConsoleCoords;
	static int      ConsoleColorTableWin[] = { 0x00, 0x0F, 0x09, 0x0A, 0x0C, 0x0E, 0x0B, 0x0D, 0x05, 0x08, 0x06 };

#endif
#ifdef LINUX
    static char     ConsoleColorTableLinuxFore[][4] = {"0;30","1;37","0;34","0;32","0;31","1;33","0;36","1;35","0;35","1;30","0;33"};
    static char     ConsoleColorTableLinuxBack[][4] = {"0;40","1;47","0;44","0;42","0;41","1;43","0;46","1;45","0;45","1;40","0;43"};

#endif


