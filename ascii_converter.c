#include "ascii_converter.h"

#ifndef INFINITY
	#define INFINITY (1.0 / 0.0)
#endif

#define ABS(x) (x < 0 ? -x : x)
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define PI 3.1415926535897932384626433832795f


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
				int xround = (int)roundf(vectors[i].x);
				// Map the coordinates right to our left-handed coordinate system.
				int yround = target->Height - 1 - (int)roundf(vectors[i].y);


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
								
				// The steps to go in x- and y-direction after processing a pixel.
				int xstep = vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].x < vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].x ? 1 : -1;
				int ystep = vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].y < vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].y ? 1 : -1;

				// The integer rounded coords. Instead used for the vectors because of performance reasons.
				int coord1x = (int)roundf(vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].x);
				int coord1y = (int)roundf(vectors[((struct TE3D_VectorIndex2*)indices)[i].i1].y);
				int coord2x = (int)roundf(vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].x);
				int coord2y = (int)roundf(vectors[((struct TE3D_VectorIndex2*)indices)[i].i2].y);
				
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

				// The gradients of the dif-vector and of the thresholds.
				float gradient = ABS((float)difvecy / (float)difvecx);
				float threshold_horizontal_45 = gradient * 0.9f;
				float threshold_vertical_45 = gradient * 1.1f;

				char45 = ((difvecx < 0 && difvecy < 0) || (difvecx > 0 && difvecy > 0)) ? '/' : '\\';

				// The current processing coordinates.
				int linex = coord1x;
				int liney = coord1y;

				while (difvecx * xstep > 0 || difvecy * ystep > 0)
				{
					// Calculate z.
					cz = z1 + dz * clen / linelen;

					// Select char.
					if (difvecy == 0)
						// Horizontal lines.
						goto HORIZONTAL_LINE;
					else if (difvecx == 0)
						// Vertical lines.
						goto VERTICAL_LINE;
				
				
					// Calculate gradient.
					gradient = ABS((float)difvecy / (float)difvecx);
					
											
					if (gradient <= threshold_horizontal_45)
					{
HORIZONTAL_LINE:
						
						// Char: _
						if (cz >= clipnear && cz <= clipfar &&
							linex >= 0 && linex < target->Width &&
							liney >= 0 && liney < target->Height)
						{
							if (zBuffer[linex + (target->Height - liney - 1) * target->Width] >= cz)
							{
								target->Pixels[linex + (target->Height - liney - 1) * target->Width].Char = '_';
								target->Pixels[linex + (target->Height - liney - 1) * target->Width].Color = colormap[i];
								zBuffer[linex + (target->Height - liney - 1) * target->Width] = cz;
							}
						}

						linex += xstep;
						// Update difference vector.
						difvecx -= xstep;
					}
					else if (gradient >= threshold_vertical_45)
					{
VERTICAL_LINE:

						// Char: |
						if (cz >= clipnear && cz <= clipfar &&
							linex >= 0 && linex < target->Width &&
							liney >= 0 && liney < target->Height)
						{
							if (zBuffer[linex + (target->Height - liney - 1) * target->Width] >= cz)
							{
								target->Pixels[linex + (target->Height - liney - 1) * target->Width].Char = '|';
								target->Pixels[linex + (target->Height - liney - 1) * target->Width].Color = colormap[i];
								zBuffer[linex + (target->Height - liney - 1) * target->Width] = cz;
							}
						}
						liney += ystep;
						// Update difference vector.
						difvecy -= ystep;
					}
					else
					{
						// Char: \ or /
						if (cz >= clipnear && cz <= clipfar &&
							linex >= 0 && linex < target->Width &&
							liney >= 0 && liney < target->Height)
						{
							if (zBuffer[linex + (target->Height - liney - 1) * target->Width] >= cz)
							{
								// When backslash appears the moves change a bit because the underscore doesn't match the backslash in the next right field.
								if (char45 == '\\')
								{
									target->Pixels[linex + (target->Height - liney) * target->Width].Char = char45;
									target->Pixels[linex + (target->Height - liney) * target->Width].Color = colormap[i];
									zBuffer[linex + (target->Height - liney) * target->Width] = cz;
								}
								else
								{
									target->Pixels[linex + (target->Height - liney - 1) * target->Width].Char = char45;
									target->Pixels[linex + (target->Height - liney - 1) * target->Width].Color = colormap[i];
									zBuffer[linex + (target->Height - liney - 1) * target->Width] = cz;
								}
							}
						}

						linex += xstep;
						liney += ystep;
						// Update difference vector.
						difvecx -= xstep;
						difvecy -= ystep;
					}

					clen += clenfactor;
																
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
