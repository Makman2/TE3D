#include "geometry.h"

// Constructs a cube mesh and adds it to the specified model.
void TE3D_Geometry_ConstructCube(struct TE3D_Model4f* model, float cubesize, struct TE3D_Vector3f cubeoffset)
{
	struct TE3D_Vector4f cube[] = {TE3D_Vector4f_N(cubeoffset.x - cubesize / 2, cubeoffset.y - cubesize / 2, cubeoffset.z - cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x + cubesize / 2, cubeoffset.y - cubesize / 2, cubeoffset.z - cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x - cubesize / 2, cubeoffset.y + cubesize / 2, cubeoffset.z - cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x + cubesize / 2, cubeoffset.y + cubesize / 2, cubeoffset.z - cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x - cubesize / 2, cubeoffset.y - cubesize / 2, cubeoffset.z + cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x + cubesize / 2, cubeoffset.y - cubesize / 2, cubeoffset.z + cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x - cubesize / 2, cubeoffset.y + cubesize / 2, cubeoffset.z + cubesize / 2, 1),
								   TE3D_Vector4f_N(cubeoffset.x + cubesize / 2, cubeoffset.y + cubesize / 2, cubeoffset.z + cubesize / 2, 1)};

	ArrayList_AddRange(&model->Vectors, cube, sizeof(cube) / sizeof(cube[0]));

	if (model->Format == TE3D_VECTORFORMAT_LINES)
	{
		struct TE3D_VectorIndex2 indices[] = {TE3D_VectorIndex2_N(model->Vectors.count + 0, model->Vectors.count + 1),
											  TE3D_VectorIndex2_N(model->Vectors.count + 0, model->Vectors.count + 2),
											  TE3D_VectorIndex2_N(model->Vectors.count + 1, model->Vectors.count + 3),
											  TE3D_VectorIndex2_N(model->Vectors.count + 2, model->Vectors.count + 3),
											  TE3D_VectorIndex2_N(model->Vectors.count + 4, model->Vectors.count + 5),
											  TE3D_VectorIndex2_N(model->Vectors.count + 4, model->Vectors.count + 6),
											  TE3D_VectorIndex2_N(model->Vectors.count + 5, model->Vectors.count + 7),
											  TE3D_VectorIndex2_N(model->Vectors.count + 6, model->Vectors.count + 7),
											  TE3D_VectorIndex2_N(model->Vectors.count + 0, model->Vectors.count + 4),
											  TE3D_VectorIndex2_N(model->Vectors.count + 1, model->Vectors.count + 5),
											  TE3D_VectorIndex2_N(model->Vectors.count + 2, model->Vectors.count + 6),
											  TE3D_VectorIndex2_N(model->Vectors.count + 3, model->Vectors.count + 7)};

		ArrayList_AddRange(&model->Indices, indices, sizeof(indices) / sizeof(indices[0]));

	}
	else if (model->Format == TE3D_VECTORFORMAT_TRIANGLES)
	{

		struct TE3D_VectorIndex3 indices[] = {TE3D_VectorIndex3_N(model->Vectors.count + 0, model->Vectors.count + 1, model->Vectors.count + 2),
											  TE3D_VectorIndex3_N(model->Vectors.count + 1, model->Vectors.count + 3, model->Vectors.count + 2),
											  TE3D_VectorIndex3_N(model->Vectors.count + 4, model->Vectors.count + 5, model->Vectors.count + 6),
											  TE3D_VectorIndex3_N(model->Vectors.count + 5, model->Vectors.count + 7, model->Vectors.count + 6),
											  TE3D_VectorIndex3_N(model->Vectors.count + 0, model->Vectors.count + 5, model->Vectors.count + 4),
											  TE3D_VectorIndex3_N(model->Vectors.count + 0, model->Vectors.count + 1, model->Vectors.count + 5),
											  TE3D_VectorIndex3_N(model->Vectors.count + 1, model->Vectors.count + 7, model->Vectors.count + 5),
											  TE3D_VectorIndex3_N(model->Vectors.count + 1, model->Vectors.count + 3, model->Vectors.count + 7),
											  TE3D_VectorIndex3_N(model->Vectors.count + 3, model->Vectors.count + 6, model->Vectors.count + 7),
											  TE3D_VectorIndex3_N(model->Vectors.count + 3, model->Vectors.count + 2, model->Vectors.count + 6),
											  TE3D_VectorIndex3_N(model->Vectors.count + 2, model->Vectors.count + 4, model->Vectors.count + 6),
											  TE3D_VectorIndex3_N(model->Vectors.count + 2, model->Vectors.count + 0, model->Vectors.count + 4)};

		ArrayList_AddRange(&model->Indices, indices, sizeof(indices) / sizeof(indices[0]));

	}
}
