#pragma once

#include "graphics.h"

//Stellt den Zeichenbuffer für die Zeichenfunktionen dar


//Stellt ein Polygon bestehend aus Linien dar
struct TE3D_PolygonLine{


};




//Matrixkonfiguration
void TE3D_View_SetPosition(float x, float y, float z);
void TE3D_View_SetLookAt(float x, float y, float z);
void TE3D_View_SetHead(float x, float y, float z);
void TE3D_View_SetFOV(float x);
void TE3D_View_SetRatio(float y);
void TE3D_View_SetScale(float z, float a);
void TE3D_View_UpdateMatrix();


//Zeichenoperationen
void TE3D_Draw_RawPoint(int x, int y);

//Initalisierung
void TE3D_CreateRenderBuffer(int width, int legth);	//Initalisiert den RenderBuffer
void TE3D_FreeRenerBuffer();						//Gibt den Renderbuffer wieder frei


//void TE3D_Draw_SwapBuffers();





