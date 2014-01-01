#include "graphics.h"
#include "text.h"
#include <cmath>
#include "GL\glew.h"
#include "GL\wglew.h"

void draw::setLineWidth(float size){
	glLineWidth (size);
}
void draw::setPointWidth(float size){
	glPointSize(size);
}
void draw::setLineMode(int mode,float param){

	switch(mode){
	case LINEMODE_FULL:
		{
			glDisable(GL_LINE_STIPPLE);

		}
		break;
	case LINEMODE_STRIPPLE:
		{
			glEnable(GL_LINE_STIPPLE);
			glLineStipple (param,0x0f0f);	
		}
		break;
	default:
		break;

	}


}


void draw::polygon(float *x,float *y,int size){
	glBegin(GL_LINE_STRIP);
	for(int i = 0;i<size;i++){
		glVertex2f(x[i],y[i]);
	}
	glVertex2f(x[0],y[0]);
	glEnd();
}
void draw::fillPolygon(float *x,float *y,int size){
	glBegin(GL_POLYGON);
	for(int i = 0;i<size;i++){
		glVertex2f(x[i],y[i]);
	}
	glVertex2f(x[0],y[0]);
	glEnd();
}

void draw::rectangle(float x1,float y1,float x2,float y2){
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y1);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glVertex2f(x1,y1);
	glEnd();
}
void draw::fillRectangle(float x1,float y1,float x2,float y2){
	glBegin(GL_QUADS);
	glVertex2f(x1,y1);
	glVertex2f(x2,y1);
	glVertex2f(x2,y2);
	glVertex2f(x1,y2);
	glEnd();
}


void draw::fillRectangleX(float x1,float y1,float x2,float y2,float param1,float param2){
	
	float high = std::abs(y2-y1);
	
  
	//glEnable (GL_LINE_STIPPLE);                      // Strichlieren einschalten
	//glLineStipple (10,0x0f0f);	 // Strichlierung festlegen

	for(float h = 0;h<high;h+=0.01f){
		glBegin(GL_LINES);
		glVertex2f(x1,y1+h);
		glVertex2f(x2,y1+h);


		glEnd();
	}


	glDisable (GL_LINE_STIPPLE); 

}


void draw::circle(float center_x, float center_y, float radius) {
  float x = 0.0f;
  float y = 0.0f;

  glBegin(GL_LINE_STRIP);
  for( double theta = 0.0; theta < PI2; theta += PI2 / 360.0 ) {
    x = center_x + ( cos( theta ) * radius );
    y = center_y + ( sin( theta ) * radius);
    glVertex2f( x, y);
  }
  glEnd();
}
void draw::fillCircle(float center_x, float center_y, float radius) {
	float x = 0.0f;
	float y = 0.0f;

	glBegin(GL_POLYGON);
	for( double theta = 0.0; theta < PI2; theta += PI2 / 360.0 ) {
		x = center_x + ( cos( theta ) * radius );
		y = center_y + ( sin( theta ) * radius);
		glVertex2f( x, y);
	}
	glEnd();
}

void draw::triangle(float x1,float y1,float x2,float y2,float x3,float y3){
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
}
void draw::fillTriangle(float x1,float y1,float x2,float y2,float x3,float y3){
	glBegin(GL_TRIANGLES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glEnd();
}





void draw::image(float x1,float y1,float x2, float y2, Texture texture){
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x1, y1,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x2, y1,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( x2,  y2,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x1,  y2,  1.0f);
	
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
}


void draw::text(FontID font,char* text,float x,float y){
	glRasterPos2f(x,y);
	//glPrint(font,text);
}




void clearScreen(float r ,float g,float b,float alpha){
	glClearColor(r,g,b,alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}
void clearScreen(RGBCol color){
	int r = (color & 0xFF0000) >> 8;
	int g = (color & 0x00FF00) >> 8;
	int b = (color & 0x0000FF) >> 8;

	float fr = 1/ 255.0f * static_cast<float>(r);
	float fg = 1/ 255.0f * static_cast<float>(g);
	float fb = 1/ 255.0f * static_cast<float>(b);

	glClearColor(fr,fg,fb,1);
	glClear(GL_COLOR_BUFFER_BIT);
}




void draw::setColor(float r,float g,float b, float alpha){
	glColor4f(r,g,b,alpha);

}
void draw::setColor(RGBCol col){
	int r = (col & 0xFF0000) >> 8;
	int g = (col & 0x00FF00) >> 8;
	int b = (col & 0x0000FF) >> 8;

	float fr = 1/ 255.0f * static_cast<float>(r);
	float fg = 1/ 255.0f * static_cast<float>(g);
	float fb = 1/ 255.0f * static_cast<float>(b);

	glColor3f(fr,fg,fb);


}





