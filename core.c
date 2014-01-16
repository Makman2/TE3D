#include "core.h"

#include "ascii_converter.h"
#include "console.h"

#include <stdlib.h>

// Adds to each field in memory the given value.
// dst: The destination address.
// val: The value to add.
// count: The number of ints in the memory to add the value to.
inline void memadd(int* dst, int val, int count)
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
		return;
	
	struct TE3D_Pipeline pipe;
	struct TE3D_Matrix4x4f initMatrix = TE3D_Transformation4x4f_Identity();
	pipe.transform3D = initMatrix;
	pipe.models3D = List_New(sizeof(struct TE3D_Model4f));
	
	struct TE3D_Surface newsurface;
	newsurface.Width = width;
	newsurface.Height = height;
	newsurface.Stride = width * sizeof(struct TE3D_ColorChar);
	newsurface.Pixels = (struct TE3D_ColorChar*)malloc(newsurface.Stride * newsurface.Height);
	pipe.asciiOut = newsurface;

	pipe.zBuffer = (float*)malloc(newsurface.Width * newsurface.Height * sizeof(float));
	
	pipe.vectorOutSize = STANDARD_VECTOR_OUTPUTBUFFER_SIZE;
	pipe.vectorOut = (struct TE3D_Vector4f*)malloc(STANDARD_VECTOR_OUTPUTBUFFER_SIZE);
	pipe.vectorIndexOut = (int*)malloc(sizeof(STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE));
	pipe.vectorOutCount = 0;
	pipe.vectorFormat = TE3D_VECTORFORMAT_TRIANGLES;

	// Initialize terminal.
	CON_init(width, height);
		
	return pipe;
}

// Releases the pipeline and all it's associated objects.
void TE3D_ReleasePipeline(struct TE3D_Pipeline* pipe)
{
	List_Release(&pipe->models3D);
	free(pipe->asciiOut.Pixels);
	free(pipe->zBuffer);
	free(pipe->vectorOut);
	free(pipe->vectorIndexOut);	
	CON_close();
}

// Resizes the output ASCII buffer of the pipeline.
void TE3D_Pipeline_ResizeBuffers(struct TE3D_Pipeline* pipe, int newwidth, int newheight)
{
	if (newwidth <= 0 || newheight <= 0)
		return;
	
	// Reset char buffer.
	pipe->asciiOut.Width = newwidth;
	pipe->asciiOut.Height = newheight;
	pipe->asciiOut.Stride = newwidth * sizeof(struct TE3D_ColorChar);
	free(pipe->asciiOut.Pixels);
	pipe->asciiOut.Pixels = (struct TE3D_ColorChar*)malloc(newwidth * sizeof(struct TE3D_ColorChar) * newheight);
	
	// Reset z-buffer.
	free(pipe->zBuffer);
	pipe->zBuffer = (float*)malloc(newwidth * newheight * sizeof(float));
}

// Transforms all vectors and copies them to the vector output buffer.
void TE3D_Pipeline_Transform(struct TE3D_Pipeline* pipe)
{
	TE3D_Model4f* element;
	TE3D_Vector4f* vecbufferPos = pipe->vectorOut;
	int vectorscount = 0;
	int* indexbufferPos = pipe->vectorIndexOut;
	
	for (int i = 0; i < pipe->models3D.count; i++)
	{
		// Get current list element.
		element = (TE3D_Model4f*)List_At(&pipe->models3D, i);
		
		// If the buffer format matches, copy.
		if (element->isActive && element->format == pipe->vectorFormat)
		{
			memcpy(vecbufferPos, element->vectors.items, element->vectors.count * sizeof(TE3D_Vector4f));
			vecbufferPos += element->vectors.count;

			// Now check if the vector format is indiced. If so, you must adjust the indices if copied behind the other indices.
			if (pipe->vectorFormat == TE3D_VECTORFORMAT_LINES)
			{
				// Copy line indices.
				memcpy(indexbufferPos, element->indices.items, element->indices.count * sizeof(TE3D_VectorIndex2));
				// Adjust indices.
				memadd(indexbufferPos, vectorscount, element->indices.count * sizeof(TE3D_VectorIndex2) / sizeof(int));

				indexbufferPos += sizeof(TE3D_VectorIndex2) / sizeof(int) * element->indices.count;
			}
			else if(pipe->vectorFormat == TE3D_VECTORFORMAT_TRIANGLES)
			{
				// Copy triangle indices.
				memcpy(indexbufferPos, element->indices.items, element->indices.count * sizeof(TE3D_VectorIndex3));
				// Adjust indices.
				memadd(indexbufferPos, vectorscount, element->indices.count * sizeof(TE3D_VectorIndex3) / sizeof(int));

				indexbufferPos += sizeof(TE3D_VectorIndex3) / sizeof(int) * element->indices.count;
			}
			
			vectorscount += element->vectors.count;

		}
	}

	// Transform the vectors.
	// Maybe it's possible to part up the work to threads (may 4-8 ones).
	for (int i = 0; i < vectorscount; i++)
	{
		pipe->vectorOut[i] = TE3D_Matrix4x4f_mul4(pipe->transform3D, pipe->vectorOut[i]);
		
		// Divide the w-component of vector.
		pipe->vectorOut[i].x /= pipe->vectorOut[i].w;
		pipe->vectorOut[i].y /= pipe->vectorOut[i].w;
		pipe->vectorOut[i].z /= pipe->vectorOut[i].w;
	}

	pipe->vectorOutCount = vectorscount;

	// Do 2D work here.


}

// Converts the vector to ASCII-Art.
void TE3D_Pipeline_RenderASCII(struct TE3D_Pipeline* pipe)
{
	TE3D_ASCII_Convert(pipe->vectorOut, pipe->vectorOutCount, &pipe->asciiOut, pipe->vectorIndexOut, pipe->vectorFormat, pipe->zBuffer);
}

// Flushes the current surface to the console.
void TE3D_Pipeline_FlushConsole(struct TE3D_Pipeline* pipe)
{
	// Workaround for console. Redefine new global accessible buffer or buffer in struct. Squeezes out performance.
	for (int x = 0; x < pipe->asciiOut.Width; x++)
		for (int y = 0; y < pipe->asciiOut.Height; x++)
		{
			CON_setCharacter(pipe->asciiOut.Pixels[x + y * pipe->asciiOut.Stride].Char, x, y, 0, CONSOLECOLOR_WHITE, CONSOLECOLOR_WHITE);
		}

	CON_flushBuffer();
}

// Applies complete rendering and flushes the console.
void TE3D_Pipeline_Render(struct TE3D_Pipeline* pipe)
{
	TE3D_Pipeline_Transform(pipe);
	TE3D_Pipeline_RenderASCII(pipe);
	TE3D_Pipeline_FlushConsole(pipe);
}

// Resizes the vector output buffer.
void TE3D_Pipeline_ResizeVectorBuffer(struct TE3D_Pipeline* pipe, int newcount)
{
	pipe->vectorOut = (struct TE3D_Vector4f*)realloc(pipe->vectorOut, newcount * sizeof(struct TE3D_Vector4f));
}

// Changes the vector format.
void TE3D_Pipeline_ChangeVectorFormat(struct TE3D_Pipeline* pipe, enum TE3D_VectorFormat format)
{
	if (format == TE3D_VECTORFORMAT_POINTS)
	{
		if (pipe->vectorIndexOut)
			free(pipe->vectorIndexOut);
	}
	else if(format == TE3D_VECTORFORMAT_LINES || format == TE3D_VECTORFORMAT_TRIANGLES)
	{
		if (!pipe->vectorIndexOut)
			pipe->vectorIndexOut = (int*)malloc(STANDARD_VECTOR_INDEX_OUTPUTBUFFER_SIZE);
	}
}

// Resizes the vector output index buffer.
void TE3D_Pipeline_ResizeVectorIndexBuffer(struct TE3D_Pipeline* pipe, int newcount)
{
	if (pipe->vectorFormat == TE3D_VECTORFORMAT_LINES)
		pipe->vectorIndexOut = (int*)realloc(pipe->vectorOut, newcount * sizeof(struct TE3D_VectorIndex2));
	else if(pipe->vectorFormat == TE3D_VECTORFORMAT_TRIANGLES)
		pipe->vectorIndexOut = (int*)realloc(pipe->vectorOut, newcount * sizeof(struct TE3D_VectorIndex3));
}