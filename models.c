#include "models.h"

// Creates a new model.
struct TE3D_Model4f TE3D_Model4f_New(struct TE3D_VectorFormat format)
{
	struct TE3D_Model4f result;
	result.vectors = ArrayList_New(sizeof(TE3D_Vector4f));
	
	switch (format)
	{
		case TE3D_VECTORFORMAT_PIXELS:
			result.indices = NULL;
			break;
		
		case TE3D_VECTORFORMAT_LINES:
			result.vectors = ArrayList_New(sizeof(TE3D_VectorIndex2));
			break;
			
		case TE3D_VECTORFORMAT_TRIANGLES:
			result.vectors = ArrayList_New(sizeof(TE3D_VectorIndex3));
			break;
	}
	
	result.isActive = true;
	result.format = format;
}