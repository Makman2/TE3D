#include "models.h"


// Creates a new model.
struct TE3D_Model4f TE3D_Model4f_New(enum TE3D_VectorFormat format)
{
	struct TE3D_Model4f result;
	result.Name = NULL;
	
	result.Vectors = ArrayList_New(sizeof(struct TE3D_Vector4f));
	
	switch (format)
	{
		case TE3D_VECTORFORMAT_POINTS:
			result.Indices.count = 0;
			result.Indices.items = NULL;
			result.Indices.typesize = 0;
			break;
		
		case TE3D_VECTORFORMAT_LINES:
			result.Vectors = ArrayList_New(sizeof(struct TE3D_VectorIndex2));
			break;
			
		case TE3D_VECTORFORMAT_TRIANGLES:
			result.Vectors = ArrayList_New(sizeof(struct TE3D_VectorIndex3));
			break;
	}
	
	result.Colors = ArrayList_New(sizeof(enum ConsoleColor));
	
	result.IsActive = true;
	result.Format = format;

	return result;
}

// Transforms the elements in the model.
void TE3D_Model4f_Transform(struct TE3D_Model4f* model, struct TE3D_Matrix4x4f matrix)
{
	// Iterate over each vector and transform it.
	for(int i = 0; i < model->Vectors.count; i++)
	{
		((struct TE3D_Vector4f*)model->Vectors.items)[i] = TE3D_Matrix4x4f_mul4(matrix, ((struct TE3D_Vector4f*)model->Vectors.items)[i]);
	}
}

// Translates the model.
void TE3D_Model4f_Translate(struct TE3D_Model4f* model, struct TE3D_Vector3f move)
{
	TE3D_Model4f_Transform(model, TE3D_Transformation4x4f_Translation(move.x, move.y, move.z));
}

// Scales the model.
void TE3D_Model4f_Scale(struct TE3D_Model4f* model, float factor)
{
	TE3D_Model4f_Transform(model, TE3D_Transformation4x4f_Scale(factor, factor, factor));
}

// Rotates the model.
void TE3D_Model4f_Rotate(struct TE3D_Model4f* model, struct TE3D_Vector3f axis, struct TE3D_Vector3f offset, double angle)
{
	TE3D_Model4f_Transform(model, TE3D_Transformation4x4f_Rotate(axis, offset, angle));
}

// Rotates the model over the x-axis.
void TE3D_Model4f_RotateX(struct TE3D_Model4f* model, double angle)
{
	TE3D_Model4f_Transform(model, TE3D_Transformation4x4f_RotateX(angle));
}

// Rotates the model over the y-axis.
void TE3D_Model4f_RotateY(struct TE3D_Model4f* model, double angle)
{
	TE3D_Model4f_Transform(model, TE3D_Transformation4x4f_RotateY(angle));
}

// Rotates the model over the z-axis.
void TE3D_Model4f_RotateZ(struct TE3D_Model4f* model, double angle)
{
	TE3D_Model4f_Transform(model, TE3D_Transformation4x4f_RotateZ(angle));
}

// Sets the name or ID of the model.
void TE3D_Model4f_SetName(struct TE3D_Model4f* model, char* name)
{
	size_t len = strlen(name);
	model->Name = (char*)malloc(len);
	memcpy(model->Name, name, len);
}

// Releases the model.
void TE3D_Model4f_Release(struct TE3D_Model4f* model)
{
	if (model->Name)
		free(model->Name);

	ArrayList_Release(&model->Vectors);
	
	if (model->Format != TE3D_VECTORFORMAT_POINTS)
		ArrayList_Release(&model->Indices);

	ArrayList_Release(&model->Colors);
}