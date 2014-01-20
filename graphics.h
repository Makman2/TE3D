#pragma once

#include "models.h"
#include "transformation.h"
#include "console.h"

#ifndef WIN32
	#include <stdbool.h>
#endif


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
	enum ConsoleColor Color;
};

// Describes a surface of colorized chars.
struct TE3D_Surface
{
	// A pointer to the array of colorized chars.
	struct TE3D_ColorChar* Pixels;
	// The width and height of the surface.
	int Width;
	int Height;
	// The stride of the surface.
	int Stride;
};



// Creates a char surface.
// Width: The width of the surface.
struct TE3D_Surface TE3D_CreateSurface(int width, int height);

// Releases a char surface.
// surface: The surface to release.
void TE3D_ReleaseSurface(struct TE3D_Surface* surface);



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
	struct TE3D_Pixel **data;
};


struct TE3D_Polygon{
	int count;
	struct TE3D_Vector3f *data;

};