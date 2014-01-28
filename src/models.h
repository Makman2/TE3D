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
struct TE3D_VectorIndex2
{
	int i1, i2;
};

struct TE3D_VectorIndex2 TE3D_VectorIndex2_N(int i1, int i2);

/// Defines a connection between three vectors (triangle).
struct TE3D_VectorIndex3
{
	// The indices of the vectors to connect.
	int i1, i2, i3;
};

struct TE3D_VectorIndex3 TE3D_VectorIndex3_N(int i1, int i2, int i3);

/// Available vector formats.
enum TE3D_VectorFormat
{
	Points = 0,
	Lines = 1,
	Triangles = 2
};

#define TE3D_VECTORFORMAT_POINTS (enum TE3D_VectorFormat)0
#define TE3D_VECTORFORMAT_LINES (enum TE3D_VectorFormat)1
#define TE3D_VECTORFORMAT_TRIANGLES (enum TE3D_VectorFormat)2

/// Describes a model build up from vectors.
struct TE3D_Model4f
{
	/// The name or ID of the model.
	char* Name;

	/// The vectors that define the model.
	struct ArrayList Vectors;
	
	/// The indices that connect the model.
	/// Note: The array list type depends on the defined vector format.
	/// 		 TE3D_VECTORFORMAT_POINTS: indices is NULL.
	///		 TE3D_VECTORFORMAT_LINES: indices contains an arraylist of type TE3D_VectorIndex2.
	///		 TE3D_VECTORFORMAT_TRIANGLES: indices contains an arraylist of type TE3D_VectorIndex3.
	struct ArrayList Indices;

	/// The colors of the model.
	struct ArrayList Colors;

	/// Sets whether the model is rendered.
	bool IsActive;
	
	/// The vector format of this model.
	enum TE3D_VectorFormat Format;
};

/// Creates a new model.
/// @param[in] format The format of the model.
struct TE3D_Model4f TE3D_Model4f_New(enum TE3D_VectorFormat format);
/// Transforms the elements in the model.
/// @param[in] matrix The matrix to transform with.
void TE3D_Model4f_Transform(struct TE3D_Model4f* model, struct TE3D_Matrix4x4f matrix);
/// Translates the model.
/// @param[in] move The translation vector.
void TE3D_Model4f_Translate(struct TE3D_Model4f* model, struct TE3D_Vector3f move);
/// Scales the model.
/// @param[in] factor The factor to scale with.
void TE3D_Model4f_Scale(struct TE3D_Model4f* model, float factor);
/// Rotates the model.
/// @param[in] axis The rotation axis.
/// @param[in] offset The offset of the rotation axis.
/// @param[in] angle The angle of the rotation to perform.
void TE3D_Model4f_Rotate(struct TE3D_Model4f* model, struct TE3D_Vector3f axis, struct TE3D_Vector3f offset, double angle);
/// Rotates the model over the x-axis.
/// @param[in] angle: The angle of the rotation to perform.
void TE3D_Model4f_RotateX(struct TE3D_Model4f* model, double angle);
/// Rotates the model over the y-axis.
/// @param[in] angle The angle of the rotation to perform.
void TE3D_Model4f_RotateY(struct TE3D_Model4f* model, double angle);
/// Rotates the model over the z-axis.
/// @param[in] angle The angle of the rotation to perform.
void TE3D_Model4f_RotateZ(struct TE3D_Model4f* model, double angle);
/// Sets the name or ID of the model.
/// @param[in] name The name or ID to set.
void TE3D_Model4f_SetName(struct TE3D_Model4f* model, char* name);
/// Releases the model.
void TE3D_Model4f_Release(struct TE3D_Model4f* model);