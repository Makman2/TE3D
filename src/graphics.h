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

#pragma once

#include "models.h"

#ifdef LINUX
	#include <stdbool.h>
#endif


/// Describes a color with red, green and blue components.
typedef struct
{
	/// The red portion of the color.
	char R;
	/// The green portion of the color.
	char G;
	/// The blue portion of the color.
	char B;
} TE3D_Color;

// Describes a colorized char.
typedef struct
{
	/// The char.
	char Char;
	/// The color of the char.
	ConsoleColor Color;
} TE3D_ColorChar;

/// Describes a surface of colorized chars.
typedef struct
{
	/// A pointer to the array of colorized chars.
	TE3D_ColorChar* Pixels; 
	/// The background of the surface.
	ConsoleColor Background;
	/// The width and height of the surface.
	int Width;
	int Height;
	/// The stride of the surface.
	int Stride;
} TE3D_Surface;

///Describes a colored Pixel
///(Depreacted)
typedef struct
{
	///Red
	int r;
	///Green
	int g;
	///Blue
	int b;
} TE3D_Pixel;


/// Creates a char surface.
/// @param[in] width The width of the surface.
/// @param[in] height The height of the Surface.
TE3D_Surface TE3D_CreateSurface(int width, int height);

/// Releases a char surface.
void TE3D_ReleaseSurface(TE3D_Surface* surface);

/// Clears the surface with the given value.
/// @param[in] val The colorized char to clear buffer with.
void TE3D_ClearSurface(TE3D_Surface* surface, TE3D_ColorChar val);
