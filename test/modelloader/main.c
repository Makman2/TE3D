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
	int newvectors, newindices;
	struct List inputmodels;
	inputmodels = LoadWavefrontFromFile("church.obj", TE3D_VECTORFORMAT_POINTS, &newvectors, &newindices);
		
	for (int i = 0; i < inputmodels.count; i++)
	{
			List_Add(&pipe.Models, List_At(&inputmodels, i));
	}


	// Adjust the vector and indices buffer, because they're now insufficient.
	TE3D_Pipeline_ResizeVectorOutputBuffer(&pipe, newvectors);
	TE3D_Pipeline_ResizeVectorIndexOutputBuffer(&pipe, newindices);

	
	for (int i = 0; i < 50; i++)
	{
		// Set the stretch matrix. This improves the vision of the rendered scene, because the letters in the terminal are taller than wide.
		pipe.Transformation = TE3D_Transformation4x4f_Scale(1, 0.5f, 1);
	
		// Set the ortho-transformation.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_OrthogonalProjection(TE3D_Vector3f_N(1,1,1), TE3D_Vector3f_N(0,1,0)));
//		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_PerspectiveProjectionZ(45, 0, -100));

		// Add translation.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_Translation(120, 80, 0));
//		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_Translation(120, -40, 0));
		// Rotate the model.	
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_RotateY(i * 0.05));
		// Scale up.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_Scale(7, 7, 7));		
	
		// Render.
		TE3D_Pipeline_Render(&pipe);
	}

	// Release inputmodels from the Wavefront file.
	List_Release(&inputmodels);
	


	// Release the pipeline.
	TE3D_ReleasePipeline(&pipe);

}
