/*
*  Console.h
*  Enthält alle Funktionen welche zur Darstellung der Daten in der Konsole nötig sind
*  Unterscheidung zwischen Linux(Steuerzeichen) und Windows (WinAPI)
*
* */

#pragma once

#include <stdio.h>
#include "graphics.h"

#ifdef WIN32
#include <windows.h>
#endif


//Initialisiert die Konsolenausgabe
int con_init(int width, int high);
//Gibt die verwendeten Resourcen wieder frei
int con_free();
//Setzt ein Zeichen in den Ausgabebuffer
int con_setCharacter(int posX, int posY, int layer, int color);

int con_clear();
int con_resetBuffer();
int con_flush();

