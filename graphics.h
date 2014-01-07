/*
	graphics.h
	Enthält alle Funktionen welche öffentlich (von außerhalb der Biblliothek) zugreifbar sein sollen
	sowie alle zentral verwendeten gemeinsamen Struckturen (Farben,Vektoren,...)



*/


#pragma once

#include <math.h>




// Describes a 4-dimensional vector.
struct TE3D_Vector4f
{
	float x, y, z, w;
};

// Describes a 3 Dimensional Vector
struct TE3D_Vector3f{
	float x;
	float y;
	float z;
};

// Describes a 2-dimensional vector.
struct TE3D_Vector2f
{
	float x, y;
};

// Describes a 2x2 matrix.
struct TE3D_Matrix2x2f
{
	float m11, m12, m21, m22;
};

// Describes a 3x3 matrix.
struct TE3D_Matrix3x3f
{
	float m11, m12, m13, m21, m22, m23, m31, m32, m33;
};

// Describes a 4x4 matrix.
struct TE3D_Matrix4x4f
{
	float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
};





// Describes a color with red, green and blue components.
struct TE3D_Color
{
	// The red portion of the color.
	char R;
	// The green portion of the color.
	char G;
	// The blue portion of the color.
	char B;
};

// Describes a colorized char.
struct TE3D_ColorChar
{
	// The char.
	char Char;
	// The color of the char.
	TE3D_Color Color;
};

// Describes a surface of colorized chars.
struct TE3D_Surface
{
	// The colorized chars of the surface.
	TE3D_Color *Pixels;
	// The width and height of the surface.
	int Width;
	int Height;
	// The stride of the surface.
	int Stride;
};



//Describes a colored Pixel
struct TE3D_Pixel{
	int r;
	int g;
	int b;

};

//Describes the DrawBuffer for Drawingfunctions
struct TE3D_DrawBuffer{
	int width;
	int legth;
	TE3D_Pixel **data;
};


struct TE3D_Polygon{
	int count;
	TE3D_Vector3f *data;

};

