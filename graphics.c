#include "graphics.h"

// Creates a char surface.
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
void TE3D_ReleaseSurface(struct TE3D_Surface* surface)
{
	free(surface);
	
	// Reset struct values.
	surface->Width = 0;
	surface->Height = 0;
	surface->Stride = 0;
	surface->Pixels = NULL;
}