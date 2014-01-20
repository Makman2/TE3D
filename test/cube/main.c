#include <TE3D.h>

#include <stdio.h>

#define OUTPUT_WIDTH 50
#define OUTPUT_HEIGHT 50

int main()
{
	// Initialize the pipeline.
	struct TE3D_Pipeline pipe = TE3D_InitializePipeline(OUTPUT_WIDTH, OUTPUT_HEIGHT);

	// Change the vector-format, because we want to render points. The default vector format on initialization is TRIANGLES.
	TE3D_Pipeline_ChangeVectorFormat(&pipe, TE3D_VECTORFORMAT_POINTS);

	// Construct the cube.
	struct TE3D_Model4f cube = TE3D_Model4f_New(TE3D_VECTORFORMAT_POINTS);
	
	struct TE3D_Vector4f cubeverts[] = {TE3D_Vector4f_N(0,0,0,1),
										TE3D_Vector4f_N(10,0,0,1),
										TE3D_Vector4f_N(10,0,10,1),
										TE3D_Vector4f_N(0,0,10,1),
										TE3D_Vector4f_N(0,10,0,1),
										TE3D_Vector4f_N(10,10,0,1),
										TE3D_Vector4f_N(10,10,10,1),
										TE3D_Vector4f_N(0,10,10,1)};

	ArrayList_AddRange(&cube.Vectors, cubeverts, 8);
	
	// Add colors for each vertex.
	enum ConsoleColor vertcolor = CONSOLECOLOR_WHITE;
	for (int i = 0; i < cube.Vectors.count; i++)
		ArrayList_Add(&cube.Colors, &vertcolor);
	
	List_Add(&pipe.Models, &cube);

	// Set the ortho-transformation.
	pipe.Transformation = TE3D_Transformation4x4f_OrthogonalProjection(TE3D_Vector3f_N(1,1,1), TE3D_Vector3f_N(0,1,0));

	// Render.
	TE3D_Pipeline_Render(&pipe);

	// Release the pipeline.
	TE3D_ReleasePipeline(&pipe);

}