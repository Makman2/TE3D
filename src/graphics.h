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
struct TE3D_Color
{
	/// The red portion of the color.
	char R;
	/// The green portion of the color.
	char G;
	/// The blue portion of the color.
	char B;
};

// Describes a colorized char.
struct TE3D_ColorChar
{
	/// The char.
	char Char;
	/// The color of the char.
	enum ConsoleColor Color;
};

/// Describes a surface of colorized chars.
struct TE3D_Surface
{
	/// A pointer to the array of colorized chars.
	struct TE3D_ColorChar* Pixels; 
	/// The background of the surface.
	enum ConsoleColor Background;
	/// The width and height of the surface.
	int Width;
	int Height;
	/// The stride of the surface.
	int Stride;
};

///Describes a colored Pixel
///(Depreacted)
struct TE3D_Pixel{
	///Red
	int r;
	///Green
	int g;
	///Blue
	int b;

};


/// Creates a char surface.
/// @param[in] width The width of the surface.
/// @param[in] height The height of the Surface.
struct TE3D_Surface TE3D_CreateSurface(int width, int height);

/// Releases a char surface.
void TE3D_ReleaseSurface(struct TE3D_Surface* surface);

/// Clears the surface with the given value.
/// @param[in] val The colorized char to clear buffer with.
void TE3D_ClearSurface(struct TE3D_Surface* surface, struct TE3D_ColorChar val);
