#include <TE3D.h>

#include <stdio.h>

#ifdef LINUX
	// GCC triggers warning, usleep is implicitly declarated, but this is only a C99 issue. It works anyway, so just ignore it.
	#include <unistd.h>
	#define sleep(ms) usleep((ms) * 1000)
#endif

#ifdef WIN32
	#include <windows.h>
	#define sleep(ms) Sleep(ms)
#endif

#define OUTPUT_WIDTH 150
#define OUTPUT_HEIGHT 50

int main()
{
	// Initialize the pipeline.
	struct TE3D_Pipeline pipe = TE3D_InitializePipeline(OUTPUT_WIDTH, OUTPUT_HEIGHT);

	// Change the vector-format, because we want to render points. The default vector format on initialization is TRIANGLES.
	TE3D_Pipeline_ChangeVectorFormat(&pipe, TE3D_VECTORFORMAT_LINES);

	// Construct the cube.
	struct TE3D_Model4f cube = TE3D_Model4f_New(TE3D_VECTORFORMAT_LINES);
	
	struct TE3D_Vector4f cubeverts[] = {TE3D_Vector4f_N(0,0,0,1),									
										TE3D_Vector4f_N(10,0,0,1),
										TE3D_Vector4f_N(0,0,10,1),
										TE3D_Vector4f_N(10,0,10,1),
										TE3D_Vector4f_N(0,10,0,1),
										TE3D_Vector4f_N(10,10,0,1),
										TE3D_Vector4f_N(0,10,10,1),
										TE3D_Vector4f_N(10,10,10,1)};
	

	struct TE3D_VectorIndex2 indices[] = {TE3D_VectorIndex2_N(0, 1),
										  TE3D_VectorIndex2_N(0, 2),
										  TE3D_VectorIndex2_N(1, 3),
										  TE3D_VectorIndex2_N(2, 3),
										  TE3D_VectorIndex2_N(4, 5),
										  TE3D_VectorIndex2_N(4, 6),
										  TE3D_VectorIndex2_N(5, 7),
										  TE3D_VectorIndex2_N(6, 7),
										  TE3D_VectorIndex2_N(0, 4),
										  TE3D_VectorIndex2_N(1, 5),
										  TE3D_VectorIndex2_N(2, 6),
										  TE3D_VectorIndex2_N(3, 7)};

	ArrayList_AddRange(&cube.Vectors, cubeverts, 8);
	ArrayList_AddRange(&cube.Indices, indices, 12);
	
	// Add colors for each line.
	enum ConsoleColor vertcolor = CONSOLECOLOR_WHITE;
	for (int i = 0; i < cube.Indices.count; i++)
	{
		ArrayList_Add(&cube.Colors, &vertcolor);
	}
	
	List_Add(&pipe.Models, &cube);
	
	// Enter render loop.
	for (int i = 0; i < 50; i++)
	{
		// Set the stretch matrix. This improves the vision of the render scene, because the letters in the terminal are taller than wide.
		TE3D_Pipeline_SetTransformation(&pipe, TE3D_Transformation4x4f_Scale(1, 0.5f, 1));
	
		// Set the ortho-transformation.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_OrthogonalProjectionWithOffset(TE3D_Vector3f_N(0,0,1), TE3D_Vector3f_N(-20,-20,-100), TE3D_Vector3f_N(0,1,0)));
		// Scale the cubes up.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_Scale(3, 3, 3));
		// Rotate the cubes.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_RotateOrigin(TE3D_Vector3f_N(1,1,1), i * 0.05));

		// Render.
		TE3D_Pipeline_Render(&pipe);
		
		// And sleep for a while.
		//sleep(40);
	}

	// Release the pipeline.
	TE3D_ReleasePipeline(&pipe);

}
