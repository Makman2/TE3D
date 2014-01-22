#include <TE3D.h>

#include <stdio.h>

#define OUTPUT_WIDTH 150
#define OUTPUT_HEIGHT 50

int main()
{
	// Initialize the pipeline.
	struct TE3D_Pipeline pipe = TE3D_InitializePipeline(OUTPUT_WIDTH, OUTPUT_HEIGHT);

	// Change the vector-format, because we want to render points. The default vector format on initialization is TRIANGLES.
	TE3D_Pipeline_ChangeVectorFormat(&pipe, TE3D_VECTORFORMAT_POINTS);

	// Load the model.
	struct List inputmodels;
	inputmodels = LoadWavefrontFromFile("church.obj", TE3D_VECTORFORMAT_POINTS);
	
	for (int i = 0; i < inputmodels.count; i++)
	{
			List_Add(&pipe.Models, List_At(&inputmodels, i));
	}


	// Set the stretch matrix. This improves the vision of the render scene, because the letters in the terminal are taller than wide.
	pipe.Transformation = TE3D_Transformation4x4f_Scale(1, 0.5f, 1);
	
	// Set the ortho-transformation.
	pipe.Transformation = TE3D_Matrix4x4f_mul(pipe.Transformation, TE3D_Transformation4x4f_OrthogonalProjection(TE3D_Vector3f_N(1,1,1), TE3D_Vector3f_N(0,1,0)));
	// Add translation.
	pipe.Transformation = TE3D_Matrix4x4f_mul(pipe.Transformation, TE3D_Transformation4x4f_Translation(-60, 0, 0));
	// Scale up.
	// pipe.Transformation = TE3D_Matrix4x4f_mul(pipe.Transformation, TE3D_Transformation4x4f_Scale(3, 3, 3));		
	// Rotate the model.	
	// pipe.Transformation = TE3D_Matrix4x4f_mul(pipe.Transformation, TE3D_Transformation4x4f_RotateOrigin(TE3D_Vector3f_N(1,1,1), i * 0.05));

	// Render.
	TE3D_Pipeline_Render(&pipe);
	

	// Release all models (the ones in the inputmodels-list and in the pipe list).
	for (int i = 0; i < inputmodels.count; i++)
	{
		TE3D_Model4f_Release((struct TE3D_Model4f*)List_At(&inputmodels, i));
	}
	// Then release the inputmodel list.
	List_Release(&inputmodels);


	// Release the pipeline.
	TE3D_ReleasePipeline(&pipe);

}
