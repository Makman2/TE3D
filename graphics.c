#include "graphics.h"

// Creates a char surface.
struct TE3D_Surface TE3D_CreateSurface(int width, int height)
{
	// Initialize surface.
	struct TE3D_Surface surface;
	surface.Width = width;
	surface.Height = height;
	surface.Stride = sizeof(struct TE3D_ColorChar) * width;
	
	surface.Pixels = (struct TE3D_ColorChar*)malloc(sizeof(struct TE3D_ColorChar) * width * height);
	memset(surface.Pixels, 0, sizeof(struct TE3D_ColorChar) * width * height);
	
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