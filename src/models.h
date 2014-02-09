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

#include "arraylist.h"
#include "transformation.h"
#include "console.h"

#include <string.h>

#ifndef WIN32
	#include <stdbool.h>
#endif

/// Defines a connection between two vectors (line).
typedef struct
{
	int i1, i2;
} TE3D_VectorIndex2;

TE3D_VectorIndex2 TE3D_VectorIndex2_N(int i1, int i2);

// FIXME why do you use indices instead of pointers? And one more thing:
// I've never seen negative indices in my life.

/// Defines a connection between three vectors (triangle).
typedef struct
{
	// The indices of the vectors to connect.
	int i1, i2, i3;
} TE3D_VectorIndex3;

TE3D_VectorIndex3 TE3D_VectorIndex3_N(int i1, int i2, int i3);

/// Available vector formats.
typedef enum
{
	Points = 0,
	Lines = 1,
	Triangles = 2
} TE3D_VectorFormat;

#define TE3D_VECTORFORMAT_POINTS (TE3D_VectorFormat)0
#define TE3D_VECTORFORMAT_LINES (TE3D_VectorFormat)1
#define TE3D_VECTORFORMAT_TRIANGLES (TE3D_VectorFormat)2

/// Describes a model build up from vectors.
typedef struct
{
	/// The name or ID of the model.
	char* Name;

	/// The vectors that define the model.
	ArrayList Vectors;
	
	/// The indices that connect the model.
	/// Note: The array list type depends on the defined vector format.
	/// 		 TE3D_VECTORFORMAT_POINTS: indices is NULL.
	///		 TE3D_VECTORFORMAT_LINES: indices contains an arraylist of type TE3D_VectorIndex2.
	///		 TE3D_VECTORFORMAT_TRIANGLES: indices contains an arraylist of type TE3D_VectorIndex3.
	ArrayList Indices;

	/// The colors of the model.
	ArrayList Colors;

	/// Sets whether the model is rendered.
	bool IsActive;
	
	/// The vector format of this model.
	TE3D_VectorFormat Format;
} TE3D_Model4f;

/// Creates a new model.
/// @param[in] format The format of the model.
TE3D_Model4f TE3D_Model4f_New(TE3D_VectorFormat format);
/// Transforms the elements in the model.
/// @param[in] matrix The matrix to transform with.
void TE3D_Model4f_Transform(TE3D_Model4f* model, TE3D_Matrix4x4f matrix);
/// Translates the model.
/// @param[in] move The translation vector.
void TE3D_Model4f_Translate(TE3D_Model4f* model, TE3D_Vector3f move);
/// Scales the model.
/// @param[in] factor The factor to scale with.
void TE3D_Model4f_Scale(TE3D_Model4f* model, float factor);
/// Rotates the model.
/// @param[in] axis The rotation axis.
/// @param[in] offset The offset of the rotation axis.
/// @param[in] angle The angle of the rotation to perform.
void TE3D_Model4f_Rotate(TE3D_Model4f* model, TE3D_Vector3f axis, TE3D_Vector3f offset, double angle);
/// Rotates the model over the x-axis.
/// @param[in] angle: The angle of the rotation to perform.
void TE3D_Model4f_RotateX(TE3D_Model4f* model, double angle);
/// Rotates the model over the y-axis.
/// @param[in] angle The angle of the rotation to perform.
void TE3D_Model4f_RotateY(TE3D_Model4f* model, double angle);
/// Rotates the model over the z-axis.
/// @param[in] angle The angle of the rotation to perform.
void TE3D_Model4f_RotateZ(TE3D_Model4f* model, double angle);
/// Sets the name or ID of the model.
/// @param[in] name The name or ID to set.
void TE3D_Model4f_SetName(TE3D_Model4f* model, char* name);
/// Releases the model.
void TE3D_Model4f_Release(TE3D_Model4f* model);
