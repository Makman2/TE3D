#include "core.h"

#define STANDARD_CHARCOLOR CONSOLECOLOR_DEFAULT
#define STANDARD_CHAR ' '

#ifndef INFINITY
	#define INFINITY (1.0 / 0.0)
#endif

// Adds to each field in memory the given value.
// dst: The destination address.
// val: The value to add.
// count: The number of ints in the memory to add the value to.
static void memadd(int* dst, int val, int count)
{
	if (!val)
		for(int i = 0; i < count; i++)
		{
			*dst += val;
			dst++;
		}
}


// Initializes the TE3D pipeline.
struct TE3D_Pipeline TE3D_InitializePipeline(int width, int height)
{
	if (width <= 0 || height <= 0)
	{
		struct TE3D_Pipeline NULLpipe;
		memset(&NULLpipe, 0, sizeof(NULLpipe));
		return NULLpipe;
	}
	
	struct TE3D_Pipeline pipe;
	struct TE3D_Matrix4x4f initMatrix = TE3D_Transformation4x4f_Identity();
	pipe.Transformation = initMatrix;
	pipe.Models = List_New(sizeof(struct TE3D_Model4f));
	
	pipe.CharOutput = TE3D_CreateSurface(width, height);

	pipe.zBuffer = (float*)malloc(pipe.CharOutput.Width * pipe.CharOutput.Height * sizeof(float));
	
	pipe.ClipNear = 0;
	pipe.ClipFar = INFINITY;

	pipe.VectorOutputCapacity = STANDARD_VECTOR_OUTPUTBUFFER_SIZE;
	pipe.VectorOutput = (struct TE3D_Vector4f*)malloc(STANDARD_VECTOR_OUTPUTBUFFER_SIZE);
	pipe.VectorIndexOutput = malloc(sizeof(STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE));
	pipe.VectorOutputCount = 0;
	pipe.VectorIndexOutputCapacity = STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE;
	pipe.VectorFormat = TE3D_VECTORFORMAT_TRIANGLES;

	pipe.Colormap = (enum ConsoleColor*)malloc(STANDARD_COLORMAP_SIZE_VI3);

	// Initialize terminal.
	TE3D_Console_Init(width, height);
		
	return pipe;
}

// Releases the pipeline and all it's associated objects.
void TE3D_ReleasePipeline(struct TE3D_Pipeline* pipe)
{
		
	// Release each model.
	for (int i = 0; i < pipe->Models.count; i++)
		TE3D_Model4f_Release((struct TE3D_Model4f*)List_At(&pipe->Models, i));

	List_Release(&pipe->Models);
	
	TE3D_ReleaseSurface(&pipe->CharOutput);

	free(pipe->zBuffer);
	free(pipe->VectorOutput);
	free(pipe->VectorIndexOutput);	
	
	// Release console buffer.
	TE3D_Console_Close();
}

// Resizes the output ASCII buffer of the pipeline.
void TE3D_Pipeline_ResizeBuffers(struct TE3D_Pipeline* pipe, int newwidth, int newheight)
{
	if (newwidth <= 0 || newheight <= 0)
		return;
	
	// Reset char buffer.
	TE3D_ReleaseSurface(&pipe->CharOutput);
	pipe->CharOutput = TE3D_CreateSurface(newwidth, newheight);
	
	// Re-init console.
	TE3D_Console_Close();
	TE3D_Console_Init(newwidth, newheight);

	// Reset z-buffer.
	free(pipe->zBuffer);
	pipe->zBuffer = (float*)malloc(newwidth * newheight * sizeof(float));
}

// Transforms all vectors and copies them to the vector output buffer.
void TE3D_Pipeline_Transform(struct TE3D_Pipeline* pipe)
{
	struct TE3D_Model4f* element;
	struct TE3D_Vector4f* vecbufferPos = pipe->VectorOutput;
	int vectorscount = 0;
	void* indexbufferPos = pipe->VectorIndexOutput;
	int indexcount = 0;
	enum ConsoleColor* colorbufferpos = pipe->Colormap;

	for (int i = 0; i < pipe->Models.count; i++)
	{
		// Get current list element.
		element = (struct TE3D_Model4f*)List_At(&pipe->Models, i);
		
		// If the buffer format matches, copy.
		if (element->IsActive && element->Format == pipe->VectorFormat)
		{
			// Copy vectors.
			memcpy(vecbufferPos, element->Vectors.items, element->Vectors.count * sizeof(struct TE3D_Vector4f));
			vecbufferPos += element->Vectors.count;

			// Copy colormap.
			memcpy(colorbufferpos, element->Colors.items, element->Colors.count * sizeof(enum ConsoleColor));
			colorbufferpos += element->Colors.count;
			
			// Now check if the vector format is indiced. If so, you must adjust the indices if copied behind the other indices.
			if (pipe->VectorFormat == TE3D_VECTORFORMAT_LINES)
			{
				// Copy line indices.
				memcpy(indexbufferPos, element->Indices.items, element->Indices.count * sizeof(struct TE3D_VectorIndex2));
				// Adjust indices.
				memadd((int*)indexbufferPos, vectorscount, element->Indices.count * sizeof(struct TE3D_VectorIndex2) / sizeof(int));
				
				indexbufferPos = (int*)indexbufferPos + (sizeof(struct TE3D_VectorIndex2) / sizeof(int) * element->Indices.count);
				indexcount += element->Indices.count;
			}
			else if(pipe->VectorFormat == TE3D_VECTORFORMAT_TRIANGLES)
			{
				// Copy triangle indices.
				memcpy(indexbufferPos, element->Indices.items, element->Indices.count * sizeof(struct TE3D_VectorIndex3));
				// Adjust indices.
				memadd((int*)indexbufferPos, vectorscount, element->Indices.count * sizeof(struct TE3D_VectorIndex3) / sizeof(int));

				indexbufferPos = (int*)indexbufferPos + (sizeof(struct TE3D_VectorIndex3) / sizeof(int) * element->Indices.count);
				indexcount += element->Indices.count;
			}
			
			vectorscount += element->Vectors.count;
		}
	}

	// Transform the vectors.
	// Maybe it's possible to part up the work to threads (may 4-8 ones).
	for (int i = 0; i < vectorscount; i++)
	{
		pipe->VectorOutput[i] = TE3D_Matrix4x4f_mul4(pipe->Transformation, pipe->VectorOutput[i]);
		
		// Divide the w-component of vector.
		pipe->VectorOutput[i].x /= pipe->VectorOutput[i].w;
		pipe->VectorOutput[i].y /= pipe->VectorOutput[i].w;
		pipe->VectorOutput[i].z /= pipe->VectorOutput[i].w;
	}

	pipe->VectorOutputCount = vectorscount;
	pipe->VectorIndexOutputCount = indexcount;
	
}

// Converts the vector to ASCII-Art.
void TE3D_Pipeline_RenderASCII(struct TE3D_Pipeline* pipe)
{
	if (pipe->VectorFormat == TE3D_VECTORFORMAT_POINTS)
		TE3D_ASCII_Convert(pipe->VectorOutput, pipe->VectorOutputCount, &pipe->CharOutput, pipe->VectorFormat, pipe->VectorIndexOutput, pipe->zBuffer, pipe->ClipNear, pipe->ClipFar, pipe->Colormap);
	else
		TE3D_ASCII_Convert(pipe->VectorOutput, pipe->VectorIndexOutputCount, &pipe->CharOutput, pipe->VectorFormat, pipe->VectorIndexOutput, pipe->zBuffer, pipe->ClipNear, pipe->ClipFar, pipe->Colormap);
}

// Flushes the current surface to the console.
void TE3D_Pipeline_FlushConsole(struct TE3D_Pipeline* pipe)
{

	// Workaround for console. Redefine new global accessible buffer or buffer in struct. Squeezes out performance.
	for (int y = 0; y < pipe->CharOutput.Height; y++)
	{
		for (int x = 0; x < pipe->CharOutput.Width; x++)
		{
			TE3D_Console_SetCurrentColor(pipe->CharOutput.Pixels[x + y * pipe->CharOutput.Width].Color, pipe->CharOutput.Background);
			TE3D_Console_WriteChar(pipe->CharOutput.Pixels[x + y * pipe->CharOutput.Width].Char);
		}

		TE3D_Console_NewLine();
	}

	TE3D_Console_FlushBuffer();
	TE3D_Console_ResetPosition();
}

// Applies complete rendering and flushes the console.
void TE3D_Pipeline_Render(struct TE3D_Pipeline* pipe)
{
	TE3D_Pipeline_Transform(pipe);
	
	struct TE3D_ColorChar defaultchar;
	defaultchar.Char = STANDARD_CHAR;
	defaultchar.Color = STANDARD_CHARCOLOR;

	TE3D_ClearSurface(&pipe->CharOutput, defaultchar);
	TE3D_Pipeline_RenderASCII(pipe);
	TE3D_Pipeline_FlushConsole(pipe);
}

// Resizes the vector output buffer.
void TE3D_Pipeline_ResizeVectorOutputBuffer(struct TE3D_Pipeline* pipe, int newcount)
{
	if (newcount <= 0)
		return;
	
	pipe->VectorOutputCapacity = newcount * sizeof(struct TE3D_Vector4f);
	pipe->VectorOutput = (struct TE3D_Vector4f*)realloc(pipe->VectorOutput, pipe->VectorOutputCapacity);

	// If TE3D_VECTORFORMAT_POINTS is specified, we must adjust the colormap size.
	if (pipe->VectorFormat == TE3D_VECTORFORMAT_POINTS)
	{
		pipe->Colormap = (enum ConsoleColor*)realloc(pipe->Colormap, newcount * sizeof(enum ConsoleColor));
	}
}

// Changes the vector format.
void TE3D_Pipeline_ChangeVectorFormat(struct TE3D_Pipeline* pipe, enum TE3D_VectorFormat format)
{
	if (pipe->VectorFormat != format)
	{

		if (format == TE3D_VECTORFORMAT_POINTS)
		{
			if (pipe->VectorIndexOutput)
			{
				free(pipe->VectorIndexOutput);
				pipe->VectorIndexOutput = NULL;
				pipe->VectorIndexOutputCount = 0;
				pipe->VectorIndexOutputCapacity = 0;

				// Reallocate colormap memory suited for the capacity of the vectors, not the indices.
				pipe->Colormap = (enum ConsoleColor*)realloc(pipe->Colormap, pipe->VectorOutputCapacity / sizeof(struct TE3D_Vector4f) * sizeof(enum ConsoleColor));
			}
		}
		else if(format == TE3D_VECTORFORMAT_LINES || format == TE3D_VECTORFORMAT_TRIANGLES)
		{
		
			if (pipe->VectorIndexOutput)
				pipe->VectorIndexOutput = realloc(pipe->VectorIndexOutput, STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE);
			else
				pipe->VectorIndexOutput = malloc(STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE);
			
			pipe->VectorIndexOutputCount = 0;
			pipe->VectorIndexOutputCapacity = STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE;
			
			// Also adjust the colormap.
			if (format == TE3D_VECTORFORMAT_LINES)
				pipe->Colormap = (enum ConsoleColor*)realloc(pipe->Colormap, STANDARD_COLORMAP_SIZE_VI2);
			else
				pipe->Colormap = (enum ConsoleColor*)realloc(pipe->Colormap, STANDARD_COLORMAP_SIZE_VI3);
		}	
	
		pipe->VectorFormat = format;
	}

}

// Resizes the vector output index buffer.
void TE3D_Pipeline_ResizeVectorIndexOutputBuffer(struct TE3D_Pipeline* pipe, int newcount)
{
	if (pipe->VectorFormat == TE3D_VECTORFORMAT_LINES)
	{
		pipe->VectorIndexOutputCapacity = newcount * sizeof(struct TE3D_VectorIndex2);
		pipe->VectorIndexOutput = (int*)realloc(pipe->VectorIndexOutput, pipe->VectorIndexOutputCapacity);

		pipe->Colormap = (enum ConsoleColor*)realloc(pipe->Colormap, newcount * sizeof(enum ConsoleColor));
	}
	else if(pipe->VectorFormat == TE3D_VECTORFORMAT_TRIANGLES)
	{
		pipe->VectorIndexOutputCapacity = newcount * sizeof(struct TE3D_VectorIndex3);
		pipe->VectorIndexOutput = (int*)realloc(pipe->VectorIndexOutput, pipe->VectorIndexOutputCapacity);

		pipe->Colormap = (enum ConsoleColor*)realloc(pipe->Colormap, newcount * sizeof(enum ConsoleColor));
	}
}

// Prepends a transformation to the pipeline. This transformation is called at the end of the transformation chain.
void TE3D_Pipeline_PrependTransformation(struct TE3D_Pipeline* pipe, struct TE3D_Matrix4x4f matrix)
{
	pipe->Transformation = TE3D_Matrix4x4f_mul(matrix, pipe->Transformation);
}

// Appends a transformation to the pipeline. This transformation is called at the beginning of the transformation chain.
void TE3D_Pipeline_AppendTransformation(struct TE3D_Pipeline* pipe, struct TE3D_Matrix4x4f matrix)
{
	pipe->Transformation = TE3D_Matrix4x4f_mul(pipe->Transformation, matrix);
}

// Sets the far clipping plane.
void TE3D_Pipeline_SetClipping(struct TE3D_Pipeline* pipe, float clipnear, float clipfar)
{
	pipe->ClipNear = clipnear;
	pipe->ClipFar = clipfar;
}

// Sets the far clipping plane.
void TE3D_Pipeline_SetClippingNear(struct TE3D_Pipeline* pipe, float clipnear)
{
	pipe->ClipNear = clipnear;
}

// Sets the far clipping plane.
void TE3D_Pipeline_SetClippingFar(struct TE3D_Pipeline* pipe, float clipfar)
{
	pipe->ClipFar = clipfar;
}

// Sets and overrides the transformation matrix.
void TE3D_Pipeline_SetTransformation(struct TE3D_Pipeline* pipe, struct TE3D_Matrix4x4f matrix)
{
	pipe->Transformation = matrix;
}
