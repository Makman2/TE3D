/* interface.h
 *
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

#pragma once
#include "graphics.h"

//Initialisation
extern void TE3D_Init();
//Deinitialisation
extern void TE3D_Exit();


//Matrixkonfiguration
extern void TE3D_View_SetPosition(float x, float y, float z);
extern void TE3D_View_SetLookAt(float x, float y, float z);
extern void TE3D_View_SetHead(float x, float y, float z);
extern void TE3D_View_SetFOV(float x);
extern void TE3D_View_SetRatio(float y);
extern void TE3D_View_SetScale(float z, float a);
extern void TE3D_View_UpdateMatrix();

//2D (without Tranformation)

extern int TE3D_Draw_2DLine(TE3D_Vector2f pos1, TE3D_Vector2f pos2);
extern int TE3D_Draw_2DRectangle(TE3D_Vector2f pos1,TE3D_Vector2f pos2);


//3D




//Console

extern int TE3D_Draw_Flush();




//other Functions


extern int getErrorText(int errorCode);


