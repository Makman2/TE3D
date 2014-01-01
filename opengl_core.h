
#pragma once
#include <windows.h>
#include "graphics.h"

//Initialisiert OpenGL unter Windows, HINSTANCE notwendig
int OGL_InitOpenGLWin(HINSTANCE hInst);

//Rotiert die Weltmatrix
void OGL_rotateWorldMatrix(float angle);
//Verschiebt die Weltmatrix
void OGL_translateWorldMatrix(struct Vector3f vec);





//Schreibt das OpenGL Bild in einen Framebuffer
int OGL_getFrameBuffer(struct *TE3D surface);


void OGL_clearScreen();
void OGL_drawLine(struct Vector3f v1, struct Vector3f v2);

