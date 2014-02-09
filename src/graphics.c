/*
 * Copyright (C) 2014 Mischa Krüger
 * Copyright (C) 2014 Ammar Al-Qaiser
 * Copyright (C) 2014 Frank Zimdars
 * Copyright (C) 2014 Gordon Kemsies
 * Copyright (C) 2014 Lasse Schuirmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "graphics.h"

// Creates a char surface.
TE3D_Surface TE3D_CreateSurface(int width, int height)
{
	// Initialize surface.
	TE3D_Surface surface;
	surface.Width = width;
	surface.Height = height;
	surface.Stride = sizeof(TE3D_ColorChar) * width;
	
	surface.Pixels = (TE3D_ColorChar*)malloc(sizeof(TE3D_ColorChar) * width * height);
	memset(surface.Pixels, 0, sizeof(TE3D_ColorChar) * width * height);
	
	surface.Background = CONSOLECOLOR_DEFAULT;

	return surface;	
}

// Releases a char surface.
void TE3D_ReleaseSurface(TE3D_Surface* surface)
{
	free(surface->Pixels);
	
	// Reset struct values.
	surface->Width = 0;
	surface->Height = 0;
	surface->Stride = 0;
	surface->Background = CONSOLECOLOR_DEFAULT;
	surface->Pixels = NULL;
}

// Clears the surface with the given value.
void TE3D_ClearSurface(TE3D_Surface* surface, TE3D_ColorChar val)
{
	for (int i = 0; i < surface->Width * surface->Height; i++)
	{
		surface->Pixels[i] = val;
	}
}
