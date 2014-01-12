#pragma once

#include "models.h"

#include "arraylist.h"
#include "graphics.h"

#ifndef WIN32
	#include <stdbool.h>
#endif

// Defines a connection between two vectors (line).
struct TE3D_VectorIndex2
{
	int i1, i2;
};

// Defines a connection between three vectors (triangle).
struct TE3D_VectorIndex3
{
	// The indices of the vectors to connect.
	int i1, i2, i3;
};

// Describes a model build up from vectors.
struct TE3D_Model4f
{
	// The vectors that define the model.
	struct ArrayList vectors;
	
	// The indices that connect the model.
	// Note: The array list type depends on the defined vector format.
	// 		 TE3D_VECTORFORMAT_POINTS: indices is NULL.
	//		 TE3D_VECTORFORMAT_LINES: indices contains an arraylist of type TE3D_VectorIndex2.
	//		 TE3D_VECTORFORMAT_TRIANGLES: indices contains an arraylist of type TE3D_VectorIndex3.
	struct ArrayList indices;
	
	// Sets if the model is rendered.
	bool isActive;
	
	// The vector format of this model.
	struct TE3D_VectorFormat format;
};

// Creates a new model.
// format: The format of the model.
struct TE3D_Model4f TE3D_Model4f_New(struct TE3D_VectorFormat format);