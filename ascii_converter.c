#include "ascii_converter.h"

#ifndef INFINITY
	#define INFINITY (1.0 / 0.0)
#endif

#define THRESHOLD_HORIZONTAL_45 0.92387953251128675612818318939679f //cos(45/2 °)
#define THRESHOLD_VERTICAL_45 0.3826834323650897717284599840304f //cos(45 + 45/2 °)

#define MAX(x,y) (x > y ? x : y)

/*
static void memsetd(double* dst, double value, int count)
{
	for (int i = 0; i < count; i++)
	{
		(*dst) = value;
		dst++;
	}
}
*/

static void memsetf(float* dst, float value, int count)
{
	for (int i = 0; i < count; i++)
	{
		(*dst) = value;
		dst++;
	}
}



// Converts vectors to an ASCII-art-representation and writes them to the target TE3D_Surface.
bool TE3D_ASCII_Convert(struct TE3D_Vector4f* vectors, int count, struct TE3D_Surface* target, enum TE3D_VectorFormat format, void* indices, float* zBuffer, float clipnear, float clipfar, enum ConsoleColor* colormap)
{
	// If z-Buffer is NULL, create own one.
	if (!zBuffer)
		zBuffer = (float*)malloc(target->Width * target->Height * sizeof(float));

	// Clear z-buffer.
	memsetf(zBuffer, INFINITY, target->Width * target->Height);

	// -- Fragt ab, welches Format für die Verbindung der Vektoren gewählt wurde.
	switch (format)
	{
		case TE3D_VECTORFORMAT_POINTS:
			// No connections, just draw the vector points.
			// But if indices is not NULL, something may went not right, so exit function.
			if (indices != NULL)
				return false;

			// Iterate over each vector and assign color.
			for (int i = 0; i < count; i++)
			{
				int xround = (int)round(vectors[i].x);
				// Map the coordinates right to our left-handed coordinate system.
				int yround = target->Height - 1 - (int)round(vectors[i].y);


				if (vectors[i].z >= clipnear && vectors[i].z <= clipfar &&
					xround >= 0 && xround < target->Width &&
					yround >= 0 && yround < target->Height)
				{
					if (zBuffer[xround + yround * target->Width] >= vectors[i].z)
					{
						zBuffer[xround + yround * target->Width] = vectors[i].z;
						target->Pixels[xround + yround * target->Width].Char = '.';
						target->Pixels[xround + yround * target->Width].Color = colormap[i];
					}
				}
			}

			break;

		// -- Hier wollen wir Linien zwischen den Vektoren zeichnen. Dazu sollte sich ein Array vom Typ TE3D_VectorIndex2 in 'indices' befinden.
		case TE3D_VECTORFORMAT_LINES:
			// Line connections.
			// If indices is NULL the function must exit.
			if (!indices)
				return false;
				
			// Iterate over each line index.
			for (int i = 0; i < count; i++)
			{
				// The precomputed char for the 45° angle.				
				char char45;
				// Holds the current angle.
				float angle;
				
				// The steps to go in x- and y-direction after processing a pixel.
				int xstep = vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].x < vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].x ? 1 : -1;
				int ystep = vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].y < vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].y ? 1 : -1;

				// The integer rounded coords. Instead used for the vectors because of performance reasons.
				int coord1x = (int)round(vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].x);
				int coord1y = (int)round(vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].y);
				int coord2x = (int)round(vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].x);
				int coord2y = (int)round(vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].y);
				
				// The z-component of the first line vector.
				float z1 = vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].z;
				// The difference of the z-components from v1 and v2.
				float dz = vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].z - z1;
				// Holds the current z-value of processed vector.
				float cz;
				// Holds the current line length of the processing step (needed for calculating z-buffer).
				float clen = 0;

				// The coordinate difference of v1 and v2.
				int difvecx = coord2x - coord1x;
				int difvecy = coord2y - coord1y;

				// The whole length of the line.
				float linelen = sqrtf(difvecx * difvecx + difvecy * difvecy);
				// The factor to increment clen. This variable holds the step-width for the line when processing z.
				float clenfactor = linelen / MAX(difvecx, difvecy);
				

				char45 = ((difvecx < 0 && difvecy < 0) || (difvecx > 0 && difvecy > 0)) ? '\\' : '/';

				// The current processing coordinates.
				int linex = coord1x;
				int liney = coord1y;

				while (linex != coord2x || liney != coord2y)
				{
					// Calculate z.
					cz = z1 + dz * clen / linelen;
									
					// Calculate angle.
					angle = linex / sqrtf(linex * linex + liney * liney);

					// Select char.
					if (angle > THRESHOLD_HORIZONTAL_45)
					{
						// Char: _
						if (zBuffer[linex + liney * target->Width] >= cz)
						{
							target->Pixels[linex + liney * target->Width].Char = '_';
							zBuffer[linex + liney * target->Width] = cz;
						}

						linex += xstep;
					}
					else if (angle < THRESHOLD_VERTICAL_45)
					{
						// Char: |
						if (zBuffer[linex + liney * target->Width] >= cz)
						{
							target->Pixels[linex + liney * target->Width].Char = '|';
							zBuffer[linex + liney * target->Width] = cz;
						}

						liney += ystep;
					}
					else
					{
						// Char: \ or /
						if (zBuffer[linex + liney * target->Width] >= cz)
						{
							target->Pixels[linex + liney * target->Width].Char = char45;
							zBuffer[linex + liney * target->Width] = cz;
						}

						linex += xstep;
						liney += ystep;
					}

					clen += clenfactor;
					target->Pixels[linex + liney * target->Width].Color = colormap[i];
					
				}

			}
				
			break;

		case TE3D_VECTORFORMAT_TRIANGLES:
			// Triangle connections.
			// If indices is again NULL the function must also exit.
			if (!indices)
				return false;

			break;
	}

	return true;
}
