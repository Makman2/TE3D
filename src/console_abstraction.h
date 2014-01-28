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

// FIXME can this comment be deleted yet?
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
