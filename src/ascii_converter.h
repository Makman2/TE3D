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

#include "graphics.h"
#include "console.h"
#include <math.h>
#ifndef WIN32
	#include "stdbool.h"
#endif


/// Converts vectors to an ASCII-art-representation and writes them to the target TE3D_Surface.
/// Returns true on success.
/// @param[in] vectors: The vectors to render.
/// @param[in] count: The number of vectors. If TE3D_VECTORFORMAT_LINES or TE3D_VECTORFORMAT_TRIANGLES is specified, count contains the number of indices to render.
/// @param[in] target: The target char-surface to write into.
/// @param[in] indices: Contains the indices of the vectors to connect (see remarks for parameter 'format').
/// @param[in] format: The vertex-format. Interpretes how vertices are connected when rendered. If TE3D_VECTORFORMAT_POINTS is specified, this field
///		   has to be NULL. When specifying TE3D_VECTORFORMAT_LINES, indices[] is a pointer to an array of TE3D_VectorIndex2 structs and
///		   when specifying TE3D_VECTORFORMAT_TRIANGLES the pointer type is an array of TE3D_VectorIndex3.
/// @param[in] zBuffer: The pointer for the Z-buffer. You can set it to NULL if you don't want to get the Z-buffer, but it's recommended for performance
///			reasons at least to create one. The function automatically creates a buffer if no one specified, but that causes a performance penalty.
bool TE3D_ASCII_Convert(struct TE3D_Vector4f* vectors, int count, struct TE3D_Surface* target, enum TE3D_VectorFormat format, void* indices, float* zBuffer, float clipnear, float clipfar, enum ConsoleColor* colormap);