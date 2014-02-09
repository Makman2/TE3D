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

#define PI 3.1415926535897932384626433832795

int main()
{
	// Initialize the pipeline.
	TE3D_Pipeline pipe = TE3D_InitializePipeline(OUTPUT_WIDTH, OUTPUT_HEIGHT);

	// Change the vector-format, because we want to render points. The default vector format on initialization is TRIANGLES.
	TE3D_Pipeline_ChangeVectorFormat(&pipe, TE3D_VECTORFORMAT_POINTS);

	// Construct the cube.
	TE3D_Model4f cube = TE3D_Model4f_New(TE3D_VECTORFORMAT_POINTS);
	TE3D_Model4f cube2 = TE3D_Model4f_New(TE3D_VECTORFORMAT_POINTS);
	
	TE3D_Vector4f cubeverts[] = {TE3D_Vector4f_N(0,0,0,1),		// Bottom border
										
										TE3D_Vector4f_N(2,0,0,1),
										TE3D_Vector4f_N(4,0,0,1),
										TE3D_Vector4f_N(6,0,0,1),
										TE3D_Vector4f_N(8,0,0,1),
										TE3D_Vector4f_N(10,0,0,1),

										TE3D_Vector4f_N(0,0,2,1),
										TE3D_Vector4f_N(0,0,4,1),
										TE3D_Vector4f_N(0,0,6,1),
										TE3D_Vector4f_N(0,0,8,1),
										TE3D_Vector4f_N(0,0,10,1),

										TE3D_Vector4f_N(2,0,10,1),
										TE3D_Vector4f_N(4,0,10,1),
										TE3D_Vector4f_N(6,0,10,1),
										TE3D_Vector4f_N(8,0,10,1),
										TE3D_Vector4f_N(10,0,10,1),

										TE3D_Vector4f_N(10,0,2,1),
										TE3D_Vector4f_N(10,0,4,1),
										TE3D_Vector4f_N(10,0,6,1),
										TE3D_Vector4f_N(10,0,8,1),

										TE3D_Vector4f_N(0,10,0,1),		// Top border.
										
										TE3D_Vector4f_N(2,10,0,1),
										TE3D_Vector4f_N(4,10,0,1),
										TE3D_Vector4f_N(6,10,0,1),
										TE3D_Vector4f_N(8,10,0,1),
										TE3D_Vector4f_N(10,10,0,1),

										TE3D_Vector4f_N(0,10,2,1),
										TE3D_Vector4f_N(0,10,4,1),
										TE3D_Vector4f_N(0,10,6,1),
										TE3D_Vector4f_N(0,10,8,1),
										TE3D_Vector4f_N(0,10,10,1),

										TE3D_Vector4f_N(2,10,10,1),
										TE3D_Vector4f_N(4,10,10,1),
										TE3D_Vector4f_N(6,10,10,1),
										TE3D_Vector4f_N(8,10,10,1),
										TE3D_Vector4f_N(10,10,10,1),

										TE3D_Vector4f_N(10,10,2,1),
										TE3D_Vector4f_N(10,10,4,1),
										TE3D_Vector4f_N(10,10,6,1),
										TE3D_Vector4f_N(10,10,8,1),


										TE3D_Vector4f_N(0,2,0,1),		// Connections between borders.
										TE3D_Vector4f_N(0,4,0,1),
										TE3D_Vector4f_N(0,6,0,1),
										TE3D_Vector4f_N(0,8,0,1),
	
										TE3D_Vector4f_N(10,2,0,1),
										TE3D_Vector4f_N(10,4,0,1),
										TE3D_Vector4f_N(10,6,0,1),
										TE3D_Vector4f_N(10,8,0,1),
	
										TE3D_Vector4f_N(0,2,10,1),
										TE3D_Vector4f_N(0,4,10,1),
										TE3D_Vector4f_N(0,6,10,1),
										TE3D_Vector4f_N(0,8,10,1),
	
										TE3D_Vector4f_N(10,2,10,1),
										TE3D_Vector4f_N(10,4,10,1),
										TE3D_Vector4f_N(10,6,10,1),
										TE3D_Vector4f_N(10,8,10,1)};
	

	ArrayList_AddRange(&cube.Vectors, cubeverts, 56);
	ArrayList_AddRange(&cube2.Vectors, cubeverts, 56);
	
	// Add colors for each vertex.
	ConsoleColor vertcolor = CONSOLECOLOR_WHITE;
	ConsoleColor vertcolor2 = CONSOLECOLOR_CYAN;
	for (int i = 0; i < cube.Vectors.count; i++)
	{
		ArrayList_Add(&cube.Colors, &vertcolor);
		ArrayList_Add(&cube2.Colors, &vertcolor2);
	}
	
	List_Add(&pipe.Models, &cube);
	
	// Transform the second cube.
	TE3D_Model4f_Transform(&cube2, TE3D_Transformation4x4f_Translation(10, 10, 10));
	List_Add(&pipe.Models, &cube2);

	// Set clipping.
	TE3D_Pipeline_SetClipping(&pipe, 1, 100);


	// Enter render loop.
	for (int i = 0; i < 100; i++)
	{
		// Set the stretch matrix. This improves the vision of the render scene, because the letters in the terminal are taller than wide.
		TE3D_Pipeline_SetTransformation(&pipe, TE3D_Transformation4x4f_Scale(1, 0.5f, 1));
	
		// Set the ortho-transformation.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_PerspectiveProjectionZ(PI / 4, 1, 1, 10));
		// Scale the cubes up.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_Scale(3, 3, 3));
		// Translate the cubes to Z.
		TE3D_Pipeline_AppendTransformation(&pipe, TE3D_Transformation4x4f_Translation(50, 50, i / 5));

		// Render.
		TE3D_Pipeline_Render(&pipe);
		
		// And sleep for a while.
		sleep(40);
	}

	// Release the pipeline.
	TE3D_ReleasePipeline(&pipe);
}
