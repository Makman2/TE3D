/*

    Das Ziel dieser Datei ist die Abstraktion der Funktionen des Konsolenmoduls und die Verbindung mit den TE3D Datentypen:
    Geplant:
        - Umrechnung RGB in die Konsolenfarben
        - Umrechnung Vektoren im Einheitsraum in Konsolenkoordinaten



    Dieser Kommentar kann nach fertigstellung gerne entfernt werden

*/

#pragma once
#include "graphics.h"
#include "console.h"
#include <stdlib.h>








int CONA_writeText(TE3D_Vector2f pos,TE3D_Color color,int wrap,char *text);
int CONA_writeChar(TE3D_Vector2f pos,TE3D_Color color,char Char);
int CONA_writeRect(TE3D_Vector2f pos,TE3D_Vector2f pos,TE3D_Color,char Char);


int CONA_Init(int w,int h);




ConsoleColor CONA_CalcColor(TE3D_Color rgbColor);
