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
bool TE3D_ASCII_Convert(TE3D_Vector4f vectors[], TE3D_Surface* target, void* indices[], TE3D_VectorFormat format);