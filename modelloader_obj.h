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