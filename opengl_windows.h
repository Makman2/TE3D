/*
	
	Erweiterung für die Windowsklasse
	

	©2013 Frank Zimdars
*/


#pragma once
#include "mod_window.h"
#include "GL\glew.h"


class OpenGLWindow : public Window
{
public:
	OpenGLWindow(HINSTANCE h, int x, int y) : Window(h, x, y){

	};

	void createOpenGLContext();
	void freeOpenGLContext();
	void setOpenGLActive();
	void swapBuffers();

	HGLRC		getHRC() const; //OK
	
protected:

	HGLRC hGLRC;


};

