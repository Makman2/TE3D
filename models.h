#pragma once

#include "arraylist.h"
#include "transformation.h"
#include "console.h"

#include <string.h>

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

// Available vector formats.
enum TE3D_VectorFormat
{
	Points = 0,
	Lines = 1,
	Triangles = 2
};

#define TE3D_VECTORFORMAT_POINTS (enum TE3D_VectorFormat)0
#define TE3D_VECTORFORMAT_LINES (enum TE3D_VectorFormat)1
#define TE3D_VECTORFORMAT_TRIANGLES (enum TE3D_VectorFormat)2

// Describes a model build up from vectors.
struct TE3D_Model4f
{
	// The name or ID of the model.
	char* Name;

	// The vectors that define the model.
	struct ArrayList Vectors;
	
	// The indices that connect the model.
	// Note: The array list type depends on the defined vector format.
	// 		 TE3D_VECTORFORMAT_POINTS: indices is NULL.
	//		 TE3D_VECTORFORMAT_LINES: indices contains an arraylist of type TE3D_VectorIndex2.
	//		 TE3D_VECTORFORMAT_TRIANGLES: indices contains an arraylist of type TE3D_VectorIndex3.
	struct ArrayList Indices;

	// The colors of the model.
	struct ArrayList Colors;

	// Sets whether the model is rendered.
	bool IsActive;
	
	// The vector format of this model.
	enum TE3D_VectorFormat Format;
};

// Creates a new model.
// format: The format of the model.
struct TE3D_Model4f TE3D_Model4f_New(enum TE3D_VectorFormat format);
// Transforms the elements in the model.
// matrix: The matrix to transform with.
void TE3D_Model4f_Transform(struct TE3D_Model4f* model, struct TE3D_Matrix4x4f matrix);
// Translates the model.
// move: The translation vector.
void TE3D_Model4f_Translate(struct TE3D_Model4f* model, struct TE3D_Vector3f move);
// Scales the model.
// factor: The factor to scale with.
void TE3D_Model4f_Scale(struct TE3D_Model4f* model, float factor);
// Rotates the model.
// axis: The rotation axis.
// offset: The offset of the rotation axis.
// angle: The angle of the rotation to perform.
void TE3D_Model4f_Rotate(struct TE3D_Model4f* model, struct TE3D_Vector3f axis, struct TE3D_Vector3f offset, double angle);
// Rotates the model over the x-axis.
// angle: The angle of the rotation to perform.
void TE3D_Model4f_RotateX(struct TE3D_Model4f* model, double angle);
// Rotates the model over the y-axis.
// angle: The angle of the rotation to perform.
void TE3D_Model4f_RotateY(struct TE3D_Model4f* model, double angle);
// Rotates the model over the z-axis.
// angle: The angle of the rotation to perform.
void TE3D_Model4f_RotateZ(struct TE3D_Model4f* model, double angle);
// Sets the name or ID of the model.
// name: The name or ID to set.
void TE3D_Model4f_SetName(struct TE3D_Model4f* model, char* name);
// Releases the model.
void TE3D_Model4f_Release(struct TE3D_Model4f* model);