/*
 * Copyright (C) 2014 Mischa Kr�ger
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
#include "list.h"
#include "arraylist.h"
#include "ascii_converter.h"
#include "console.h"

#include <stdlib.h>

#define STANDARD_VECTOR_OUTPUTBUFFER_SIZE (256 * sizeof(TE3D_Vector4f))
#define STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE 1056
#define STANDARD_COLORMAP_SIZE_VI2 (STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE / \
			sizeof(TE3D_VectorIndex2) * sizeof(ConsoleColor))
#define STANDARD_COLORMAP_SIZE_VI3 (STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE / \
			sizeof(TE3D_VectorIndex3) * sizeof(ConsoleColor))

/// The standard TE3D working pipeline.
typedef struct
{
	/// The 3D-transformation matrix.
	TE3D_Matrix4x4f Transformation;

	/// Cotnains all 3D-models with their vectors.
	List Models;

	/// The vector mode.
	TE3D_VectorFormat VectorFormat;

	/// The Z-buffer.
	float* zBuffer;

	/// The clipping distance of the near plane.
	float ClipNear;
	/// The clipping distance of the far plane.
	float ClipFar;

	/// The colormap. This array assigns each point, line or triangle a color.
	ConsoleColor* Colormap;

	/**
	 * The size of the vector output buffer. Adjust it via
	 * TE3D_Pipeline_ResizeVectorOutputBuffer if memory allocation errors
	 * occur, because the transformation routine that copies all vectors
	 * together in an array doesn't check for memory overflows.
	 */
	size_t VectorOutputCapacity;
	/// The number of vectors in the vector output buffer.
	int VectorOutputCount;
	/// The vector output buffer.
	TE3D_Vector4f* VectorOutput;
	/// The vector index output buffer.
	void* VectorIndexOutput;
	/// The number of vector indices in the vector index output buffer.
	int VectorIndexOutputCount;
	/**
	 * The size of the vector index output buffer. Adjust it via
	 * TE3D_Pipeline_ResizeVectorIndexOutputBuffer if memory allocation errors
	 * occur, because the transformation routine that copies all vectors
	 * together in an array doesn't check for memory overflows.
	 */
	size_t VectorIndexOutputCapacity;

	/// The char surface for the ASCII converter output.
	/// Contains the rendered image.
	TE3D_Surface CharOutput;
} TE3D_Pipeline;



/// Initializes the TE3D pipeline.
/// @param[in] width: The initial output width.
/// @param[in]  height: The initial output height.
TE3D_Pipeline TE3D_InitializePipeline(int width, int height);

/// Releases the pipeline and all it's associated objects.
void TE3D_ReleasePipeline(TE3D_Pipeline* pipe);

/// Resizes the output ASCII buffer of the pipeline.
/// @param[in]  newwidth: The new width.
/// @param[in]  newheight: The new height.
void TE3D_Pipeline_ResizeBuffers(TE3D_Pipeline* pipe, int newwidth,
								 int newheight);

/// Transforms all vectors and copies them to the vector output buffer.
/// @param[in]  pipe Pipeline to work on
void TE3D_Pipeline_Transform(TE3D_Pipeline* pipe);

/// Converts the vector to ASCII-Art.
/// @param[in]  pipe Pipeline to work on
void TE3D_Pipeline_RenderASCII(TE3D_Pipeline* pipe);

/// Flushes the current surface to the console.
/// @param[in]  pipe Pipeline to work on
void TE3D_Pipeline_FlushConsole(TE3D_Pipeline* pipe);

/// Applies complete rendering and flushes the console.
/// @param[in]  pipe Pipeline to work on
void TE3D_Pipeline_Render(TE3D_Pipeline* pipe);

/// Resizes the vector output buffer.
/// @param[in]  newcount: The new number of TE3D_Vector4f's the output buffer should handle.
void TE3D_Pipeline_ResizeVectorOutputBuffer(TE3D_Pipeline* pipe,
											int newcount);

/// Resizes the vector output index buffer. If TE3D_VECTORFORMAT_POINTS is specified, this function returns directly.
/// @param[in]  newcount: The new number of vector indices the index output buffer should handle.
void TE3D_Pipeline_ResizeVectorIndexOutputBuffer(TE3D_Pipeline* pipe,
												 int newcount);

/// Changes the vector format.
/// @param[in]  format: The new vector format.
void TE3D_Pipeline_ChangeVectorFormat(TE3D_Pipeline* pipe,
									  TE3D_VectorFormat format);

/// Prepends a transformation to the pipeline. This transformation is called at the end of the transformation chain.
/// @param[in]  matrix: The matrix to transform with.
void TE3D_Pipeline_PrependTransformation(TE3D_Pipeline* pipe,
										 TE3D_Matrix4x4f matrix);

/**
 * Appends a transformation to the pipeline. This transformation is called at
 * the beginning of the transformation chain.
 * @param[in]  matrix: The matrix to transform with.
 */
void TE3D_Pipeline_AppendTransformation(TE3D_Pipeline* pipe,
										TE3D_Matrix4x4f matrix);

/// Sets the far clipping plane.
/// @param[in]  clipnear: The distance to the near clipping plane.
/// @param[in]  clipfar: The distance to the far clipping plane.
void TE3D_Pipeline_SetClipping(TE3D_Pipeline* pipe, float clipnear,
							   float clipfar);

/// Sets the far clipping plane.
/// @param[in]  clipnear: The distance to the near clipping plane.
void TE3D_Pipeline_SetClippingNear(TE3D_Pipeline* pipe, float clipnear);

/// Sets the far clipping plane.
/// @param[in]  clipfar: The distance to the far clipping plane.
void TE3D_Pipeline_SetClippingFar(TE3D_Pipeline* pipe, float clipfar);

/// Sets and overrides the transformation matrix.
/// @param[in]  matrix: The matrix to set.
void TE3D_Pipeline_SetTransformation(TE3D_Pipeline* pipe,
									 TE3D_Matrix4x4f matrix);

/// Adds a model to the pipeline.
/// @param[in]	model: The model to add.
void TE3D_Pipeline_AddModel(TE3D_Pipeline* pipe,
							const TE3D_Model4f* model);
