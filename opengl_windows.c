#include "stdafx.h"
#include "openGLWindow.h"


void OpenGLWindow::createOpenGLContext(){

	PIXELFORMATDESCRIPTOR pfd;
	int iFormat;


	/* set the pixel format for the DC */
	ZeroMemory(&pfd, sizeof (pfd));
	pfd.nSize = sizeof (pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	iFormat = ChoosePixelFormat(this->hDC, &pfd);
	SetPixelFormat(this->hDC, iFormat, &pfd);
	this->hGLRC = wglCreateContext(this->hDC);
	

}

void OpenGLWindow::swapBuffers(){
	SwapBuffers(this->hDC);
}

void OpenGLWindow::setOpenGLActive(){
	wglMakeCurrent(this->hDC, this->hGLRC);
}


void OpenGLWindow::freeOpenGLContext(){

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(this->hGLRC);

	//ReleaseDC(this->hWnd, this->hDC);


}

HGLRC OpenGLWindow::getHRC() const{
	return this->hGLRC;
}




