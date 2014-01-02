#pragma once

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"


//Stellt einen Pixel dar
struct TE3D_Pixel{
	int r;
	int g;
	int b;

};
//Stellt den Zeichenbuffer für die Zeichenfunktionen dar
struct TE3D_DrawBuffer{
	int width;
	int legth;
	TE3D_Pixel **data;
};

//Stellt ein Polygon bestehend aus Linien dar
struct TE3D_PolygonLine{


};
//Stellt einen 3-Dimensionalen Vektor
struct TE3D_Vector{
	float x;
	float y;
	float z;
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



void TE3D_Draw_Line(struct TE3D_Vector pos1, struct TE3D_Vector pos2);
void TE3D_Draw_Rectangle(struct TE3D_Vector pos1, struct TE3D_Vector pos2);


