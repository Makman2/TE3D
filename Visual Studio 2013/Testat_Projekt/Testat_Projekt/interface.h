/*
	interface.h

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


