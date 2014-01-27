#pragma once

#include "graphics.h"
#include "list.h"
#include "arraylist.h"
#include "ascii_converter.h"
#include "console.h"

#include <stdlib.h>

#define STANDARD_VECTOR_OUTPUTBUFFER_SIZE (256 * sizeof(struct TE3D_Vector4f))
#define STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE 1056
#define STANDARD_COLORMAP_SIZE_VI2 (STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE / sizeof(struct TE3D_VectorIndex2) * sizeof(enum ConsoleColor))
#define STANDARD_COLORMAP_SIZE_VI3 (STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE / sizeof(struct TE3D_VectorIndex3) * sizeof(enum ConsoleColor))

// The standard TE3D working pipeline.
struct TE3D_Pipeline
{
	// The 3D-transformation matrix.
	struct TE3D_Matrix4x4f Transformation;

	// Cotnains all 3D-models with their vectors.
	struct List Models;

	// The vector mode.
	enum TE3D_VectorFormat VectorFormat;

	// The Z-buffer.
	float* zBuffer;

	// The clipping distance of the near plane.
	float ClipNear;
	// The clipping distance of the far plane.
	float ClipFar;

	// The colormap. This array assigns each point, line or triangle a color.
	enum ConsoleColor* Colormap;

	// The size of the vector output buffer. Adjust it via TE3D_Pipeline_ResizeVectorOutputBuffer if memory allocation errors occur,
	// because the transformation routine that copies all vectors together in an array doesn't check for memory overflows.
	size_t VectorOutputCapacity;
	// The number of vectors in the vector output buffer.
	int VectorOutputCount;
	// The vector output buffer.
	struct TE3D_Vector4f* VectorOutput;
	// The vector index output buffer.
	void* VectorIndexOutput;
	// The number of vector indices in the vector index output buffer.
	int VectorIndexOutputCount;
	// The size of the vector index output buffer. Adjust it via TE3D_Pipeline_ResizeVectorIndexOutputBuffer if memory allocation errors occur,
	// because the transformation routine that copies all vectors together in an array doesn't check for memory overflows.
	size_t VectorIndexOutputCapacity;

	// The char surface for the ASCII converter output.
	// Contains the rendered image.
	struct TE3D_Surface CharOutput;
};



// Initializes the TE3D pipeline.
// width: The initial output width.
// height: The initial output height.
struct TE3D_Pipeline TE3D_InitializePipeline(int width, int height);

// Releases the pipeline and all it's associated objects.
void TE3D_ReleasePipeline(struct TE3D_Pipeline* pipe);

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
void TE3D_Pipeline_ResizeVectorOutputBuffer(struct TE3D_Pipeline* pipe, int newcount);

// Resizes the vector output index buffer. If TE3D_VECTORFORMAT_POINTS is specified, this function returns directly.
// newcount: The new number of vector indices the index output buffer should handle.
void TE3D_Pipeline_ResizeVectorIndexOutputBuffer(struct TE3D_Pipeline* pipe, int newcount);

// Changes the vector format.
// format: The new vector format.
void TE3D_Pipeline_ChangeVectorFormat(struct TE3D_Pipeline* pipe, enum TE3D_VectorFormat format);

// Prepends a transformation to the pipeline. This transformation is called at the end of the transformation chain.
// matrix: The matrix to transform with.
void TE3D_Pipeline_PrependTransformation(struct TE3D_Pipeline* pipe, struct TE3D_Matrix4x4f matrix);

// Appends a transformation to the pipeline. This transformation is called at the beginning of the transformation chain.
// matrix: The matrix to transform with.
void TE3D_Pipeline_AppendTransformation(struct TE3D_Pipeline* pipe, struct TE3D_Matrix4x4f matrix);

// Sets the far clipping plane.
// clipnear: The distance to the near clipping plane.
// clipfar: The distance to the far clipping plane.
void TE3D_Pipeline_SetClipping(struct TE3D_Pipeline* pipe, float clipnear, float clipfar);

// Sets the far clipping plane.
// clipnear: The distance to the near clipping plane.
void TE3D_Pipeline_SetClippingNear(struct TE3D_Pipeline* pipe, float clipnear);

// Sets the far clipping plane.
// clipfar: The distance to the far clipping plane.
void TE3D_Pipeline_SetClippingFar(struct TE3D_Pipeline* pipe, float clipfar);

// Sets and overrides the transformation matrix.
// matrix: The matrix to set.
void TE3D_Pipeline_SetTransformation(struct TE3D_Pipeline* pipe, struct TE3D_Matrix4x4f matrix);