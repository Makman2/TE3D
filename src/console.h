/*
 * Copyright (C) 2014 Mischa Krüger
 * Copyright (C) 2014 Ammar Al-Qaiser
 * Copyright (C) 2014 Frank Zimdars
 * Copyright (C) 2014 Gordon Kemsies
 * Copyright (C) 2014 Lasse Schuirmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// TODO transfer bugs to issue tracker, remove comment
/*

Console.h
Version 1.0
08.01.2014


Momentan noch vorhandene Bugs:
[Linux]
- BUG Die Hintergrundfarbe wird nicht richtig übernommen, die Vordergrundfarbe sollte jedoch stimmen
[Windows]
- BUG Die Hintergrundfarbe wird zur Hintergrundfarbe der Konsole.
	Ziel: Verhindern und durch eine extra Funktion ermöglichen wenn dieses Verhalten vom Benutzer gewünscht
[Alle]
- BUG Umlaute und Sonderzeichen in der Textausgabe funktionieren nicht
- BUG Es sind noch nicht alle Farben implementiert
- BUG Farben sind noch nicht getestet, sollte ein Farbwert nicht stimmen, müsste er noch korrigiert werden
*/

#pragma once


#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
	#include <windows.h>
	#define WINCOLOR(a,b) (b<<4)+a //Build the Win-Terminal Color, A = Foreground B= Background
#endif


#define CON_DEFAULT_SIZE_X     30
#define CON_DEFAULT_SIZE_Y     15


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

// Extended operating system specific colors for the moment not supported.
/* FIXME commented code is not allowed
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


//Colors for the Console
enum ConsoleColor{

	// Available for all operating systems.
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

/* FIXME commented code is not allowed
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

/// Writes a char to the underlying stream.
/// @param[in] chr Character to write to the Console
int TE3D_Console_WriteChar(char chr);

/// Clears the console screen.
int TE3D_Console_ClearScreen();
/// Initializes the console module.
int TE3D_Console_Init(int w, int h);
/// Closes the module.
int TE3D_Console_Close();
///Print the consoleBuffer out to the Console
int TE3D_Console_FlushBuffer();

/// Sets the position of the cursor.
///@param[in] x X-Position of the Cursor
///@param[in] y Y-Position of the Cursor
int TE3D_Console_SetPosition(int x, int y);

/// Sets the color of the following terminal chars that are printed out.
///@param[in] fg Forgroundcolor
///@param[in] fg Backroundcolor
int TE3D_Console_SetCurrentColor(enum ConsoleColor fg,enum ConsoleColor bg);

/// Moves the cursor of the console.
/// @param[in] x The x-steps to move.
/// @param[in] y The y-steps to move.
int TE3D_Console_MoveCursor(int x, int y);

/// Sets the position of the cursor to 0,0.
int TE3D_Console_ResetPosition();

/// Writes a newline.
int TE3D_Console_NewLine();

/// Retrieves the output buffer.
char* TE3D_Console_GetBuffer();
/// Retrieves the underlying stream (usually stdout).
FILE* TE3D_Console_GetStream();

/// Hides the cursor.
int TE3D_Console_HideCursor();

/// Shows the cursor.
int TE3D_Console_ShowCursor();
