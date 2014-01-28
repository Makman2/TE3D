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

#include "transformation.h"
#include "models.h"
#include "list.h"

#include <stdio.h>

// Loads a Wavefront OBJ from stream.
// file: The stream to load the data from.
// format: The format the vectors should have inside the model.
//		   Note: If TE3D_VECTORFORMAT_PIXELS or TE3D_VECTORFORMAT_LINES is specified, the faces of the wavefront file are automatically converted.
// vectorscount: The number of vertices loaded.
// indicescount: The number of indices loaded. When TE3D_VECTORFORMAT_PIXELS is specified, this parameter should be NULL.
struct List LoadWavefront(FILE* file, enum TE3D_VectorFormat format, int* vectorscount, int* indicescount);

// Loads a Wavefront OBJ from file.
// path: The path of the file.
// format: The format the vectors should have inside the model.
//		   Note: If TE3D_VECTORFORMAT_PIXELS or TE3D_VECTORFORMAT_LINES is specified, the faces of the wavefront file are automatically converted.
// vectorscount: The number of vertices loaded.
// indicescount: The number of indices loaded. When TE3D_VECTORFORMAT_PIXELS is specified, this parameter should be NULL.
struct List LoadWavefrontFromFile(char* path, enum TE3D_VectorFormat format, int* vectorscount, int* indicescount);