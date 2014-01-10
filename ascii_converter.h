#pragma once

#include "graphics.h"
#ifndef WIN32
	#include "stdbool.h"
#endif


// Converts vectors to an ASCII-art-representation and writes them to the target TE3D_Surface.
// Returns 
// vectors: The vectors to render.
// target: The target char-surface to write into.
// indices: Contains the indices of the vectors to connect (see remarks for parameter 'format').
// format: The vertex-format. Interpretes how vertices are connected when rendered. If TE3D_VECTORFORMAT_POINTS is specified, this field
//		   has to be NULL. When specifying TE3D_VECTORFORMAT_LINES, indices[] is a pointer to an array of TE3D_VectorIndex2 structs and
//		   when specifying TE3D_VECTORFORMAT_TRIANGLES the pointer type is an array of TE3D_VectorIndex3.
// zBuffer: The pointer for the Z-buffer. You can set it to NULL if you don't want to get the Z-buffer, but it's recommended for performance
//			reasons at least to create one. The function automatically creates a buffer if no one specified, but that causes a performance penalty.
// colormap: A pointer to the colormap, that contains the color for each vector. Format is 24bpp RGB. If NULL the default color is used.
bool TE3D_ASCII_Convert(TE3D_Vector4f vectors[], TE3D_Surface* target, void* indices[], TE3D_VectorFormat format, float* zBuffer, char* colormap);