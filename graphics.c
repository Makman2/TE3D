#include <stdlib.h>
#include <SDL2/SDL.h>
#ifndef WIN32
		#include <stdbool.h>
#endif

#include "graphics.h"



// Creates a char surface.
// Width: The width of the surface.
// Returns the newly created surface.
struct TE3D_Surface* TE3D_CreateSurface(int width, int height)
{
	// Allocate memory for "char-pixels" and surface and zero-initialize it.
	char* addr = calloc(sizeof(struct TE3D_Surface) + sizeof(struct TE3D_ColorChar) * width * height);
	
	// Initialize surface.
	TE3D_Surface* surface = addr;
	(*surface).Width = width;
	(*surface).Height = height;
	(*surface).Stride = sizeof(struct TE3D_ColorChar) * width;
	// Point to the area after the structure.
	(*surface).Pixels = addr + sizeof(surface);
	
	return surface;	
}

// Releases a char surface.
// surface: The surface to release.
void TE3D_ReleaseSurface(struct TE3D_Surface* surface)
{
	free(surface);
	
	// Reset struct values.
	(*surface).Width = 0;
	(*surface).Height = 0;
	(*surface).Stride = 0;
	(*surface).Pixels = NULL;
}