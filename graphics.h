#pragma once

#include "models.h"
#include "transformation.h"

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
	struct TE3D_Color Color;
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
// Returns the newly created surface.
struct TE3D_Surface* TE3D_CreateSurface(int width, int height)
{
	// Allocate memory for "char-pixels" and surface and zero-initialize it.
	struct TE3D_Surface* addr = (struct TE3D_Surface*)malloc(sizeof(struct TE3D_Surface) + sizeof(struct TE3D_ColorChar) * width * height);
	memset(addr + 1, 0, sizeof(struct TE3D_ColorChar) * width * height);
	
	// Initialize surface.
	struct TE3D_Surface* surface = addr;
	surface->Width = width;
	surface->Height = height;
	surface->Stride = sizeof(struct TE3D_ColorChar) * width;
	// Points to the area after the structure.
	surface->Pixels = (struct TE3D_ColorChar*)(addr + 1);
	
	return surface;	
}

// Releases a char surface.
// surface: The surface to release.
void TE3D_ReleaseSurface(struct TE3D_Surface* surface)
{
	free(surface);
	
	// Reset struct values.
	surface->Width = 0;
	surface->Height = 0;
	surface->Stride = 0;
	surface->Pixels = NULL;
}





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