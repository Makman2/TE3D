#pragma once

#include "graphics.h"
#include "list.h"
#include "arraylist.h"
#include "ascii_converter.h"
#include "console.h"

#include <stdlib.h>

#define STANDARD_VECTOR_OUTPUTBUFFER_SIZE (256 * sizeof(struct TE3D_Vector4f))
#define STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE (128 * sizeof(struct TE3D_VectorIndex2))

// The standard TE3D working pipeline.
struct TE3D_Pipeline
{
	// The 3D-transformation matrix.
	struct TE3D_Matrix4x4f transform3D;

	// Cotnains all 3D-models with their vectors.
	struct List models3D;

	// The vector mode.
	enum TE3D_VectorFormat vectorFormat;

	// The Z-buffer.
	float* zBuffer;

	// The size of the vector output buffer. Adjust it via TE3D_Pipeline_ResizeVectorBuffer, if memory allocation errors occurs,
	// because the transformation routine that copies the all vectors together in an array doesn't check for memory overflows.
	size_t vectorOutSize;
	// The vector output buffer.
	struct TE3D_Vector4f* vectorOut;
	// The number of vectors in the vectorOut buffer.
	int vectorOutCount;
	// The vector index output buffer.
	int* vectorIndexOut;

	// The char surface for the ASCII converter output.
	struct TE3D_Surface asciiOut;
};



// Initializes the TE3D pipeline.
// width: The initial output width.
// height: The initial output height.
struct TE3D_Pipeline TE3D_InitializePipeline(int width, int height);

// Resizes the output ASCII buffer of the pipeline.
// newwidth: The new width.
// newheight: The new height.
void TE3D_Pipeline_ResizeBuffers(struct TE3D_Pipeline* pipe, int newwidth, int newheight);

// Transforms all vectors and copies them to the vector output buffer.
void TE3D_Pipeline_Transform(struct TE3D_Pipeline* pipe);

// Converts the vector to ASCII-Art.
void TE3D_Pipeline_RenderASCII(struct TE3D_Pipeline* pipe);

// Flushes the current surface to the console.
void TE3D_Pipeline_FlushConsole(struct TE3D_Pipeline* pipe);

// Applies complete rendering and flushes the console.
void TE3D_Pipeline_Render(struct TE3D_Pipeline* pipe);

// Resizes the vector output buffer.
// newcount: The new number of TE3D_Vector4f's the output buffer should handle.
void TE3D_Pipeline_ResizeVectorBuffer(struct TE3D_Pipeline* pipe, int newcount);

// Resizes the vector output index buffer. If TE3D_VECTORFORMAT_POINTS is specified, this function returns directly.
// newcount: The new number of vector indices the index output buffer should handle.
void TE3D_Pipeline_ResizeVectorIndexBuffer(struct TE3D_Pipeline* pipe, int newcount);

// Changes the vector format.
// format: The new vector format.
void TE3D_Pipeline_ChangeVectorFormat(struct TE3D_Pipeline* pipe, enum TE3D_VectorFormat format);