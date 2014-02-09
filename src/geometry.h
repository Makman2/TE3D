#pragma once

#include "graphics.h"

/// Constructs a cube mesh and adds it to the specified model.
/// @param[in]	cubesize: The length of the cube edges.
/// @param[in]	cubeoffset: The midpoint of the cube.
void TE3D_Geometry_ConstructCube(struct TE3D_Model4f* model, float cubesize,
								 struct TE3D_Vector3f cubeoffset);
