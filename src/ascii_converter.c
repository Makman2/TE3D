/*
 * Copyright (C) 2014 Mischa Krüger
 * Copyright (C) 2014 Ammar Al-Qaiser
 * Copyright (C) 2014 Frank Zimdars
 * Copyright (C) 2014 Gordon Kemsies
 * Copyright (C) 2014 Lasse Schuirmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ascii_converter.h"

#ifndef INFINITY
	#define INFINITY (1.0 / 0.0)
#endif

#define ABS(x) (x < 0 ? -x : x)
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

static void memsetf(float* dst, float value, int count)
{
	for (int i = 0; i < count; i++)
	{
		(*dst) = value;
		dst++;
	}
}



// Converts vectors to an ASCII-art-representation and writes them to the target TE3D_Surface.
bool TE3D_ASCII_Convert(TE3D_Vector4f* vectors, int count, TE3D_Surface* target,
						TE3D_VectorFormat format, void* indices, float* zBuffer,
						float clipnear, float clipfar, ConsoleColor* colormap)
{
	// If z-Buffer is NULL, create own one.
	bool zBufferCreated;
	if (!zBuffer)
	{
		zBuffer = (float*)malloc(target->Width * target->Height * sizeof(float));
		zBufferCreated = true;
	}
	else
	{
		zBufferCreated = false;
	}

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
			{
				// Release z-Buffer if created.
				if (zBufferCreated)
					free(zBuffer);

				return false;
			}
				
			// Iterate over each line index.
			for (int i = 0; i < count; i++)
			{
				// The precomputed char for the 45° angle.				
				char char45;
								
				// The steps to go in x- and y-direction after processing a pixel.
				int xstep = vectors[((TE3D_VectorIndex2*)indices)[i].i1].x < vectors[((TE3D_VectorIndex2*)indices)[i].i2].x ? 1 : -1;
				int ystep = vectors[((TE3D_VectorIndex2*)indices)[i].i1].y < vectors[((TE3D_VectorIndex2*)indices)[i].i2].y ? 1 : -1;

				// The integer rounded coords. Instead used for the vectors because of performance reasons.
				int coord1x = (int)roundf(vectors[((TE3D_VectorIndex2*)indices)[i].i1].x);
				int coord1y = (int)roundf(vectors[((TE3D_VectorIndex2*)indices)[i].i1].y);
				int coord2x = (int)roundf(vectors[((TE3D_VectorIndex2*)indices)[i].i2].x);
				int coord2y = (int)roundf(vectors[((TE3D_VectorIndex2*)indices)[i].i2].y);
				
				// The z-component of the first line vector.
				float z1 = vectors[((TE3D_VectorIndex2*)indices)[i].i1].z;
				// The difference of the z-components from v1 and v2.
				float dz = vectors[((TE3D_VectorIndex2*)indices)[i].i2].z - z1;
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
									if (liney + 1 < target->Height)
									{
										target->Pixels[linex + (target->Height - liney) * target->Width].Char = char45;
										target->Pixels[linex + (target->Height - liney) * target->Width].Color = colormap[i];
										zBuffer[linex + (target->Height - liney) * target->Width] = cz;
									}
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
			{
				// Release z-Buffer if created.
				if (zBufferCreated)
					free(zBuffer);

				return false;
			}

			// To determine whether a point lays inside a triangle, we check if
			// s > 0, t > 0, s + t <= 1 with the planar function f(s,t) = s*(a1,a2) + t*(b1,b2) + (off1,off2)

			// Iterate over each triangle.
			for (int i = 0; i < count; i++)
			{
				// Round coordinates.
				int off1 = (int)roundf(vectors[((TE3D_VectorIndex3*)indices)[i].i1].x);;
				int off2 = (int)roundf(vectors[((TE3D_VectorIndex3*)indices)[i].i1].y);;
				int a1 = (int)roundf(vectors[((TE3D_VectorIndex3*)indices)[i].i2].x);
				int a2 = (int)roundf(vectors[((TE3D_VectorIndex3*)indices)[i].i2].y);
				int b1 = (int)roundf(vectors[((TE3D_VectorIndex3*)indices)[i].i3].x);
				int b2 = (int)roundf(vectors[((TE3D_VectorIndex3*)indices)[i].i3].y);

				// Get rectangular bounds of the triangle.
				int rectBoundXL = MAX(0, MIN(off1, MIN(a1, b1)));
				int rectBoundXR = MIN(target->Width - 1, MAX(off1, MAX(a1, b1)));
				int rectBoundYT = MAX(0, MIN(off2, MIN(a2, b2)));
				int rectBoundYB = MIN(target->Height - 1, MAX(off2, MAX(a2, b2)));

				// Get the gradients for the current triangle.
				a1 = a1 - off1;
				a2 = a2 - off2;
				b1 = b1 - off1;
				b2 = b2 - off2;

				// Get the z-values.
				float offz = vectors[((TE3D_VectorIndex3*)indices)[i].i1].z;
				float za = vectors[((TE3D_VectorIndex3*)indices)[i].i2].z - offz;
				float zb = vectors[((TE3D_VectorIndex3*)indices)[i].i3].z - offz;

				// Scanline the rectangular area of the triangle with the above condition.
				for (int x = rectBoundXL; x <= rectBoundXR; x++)
				{
					// We need the decomposition of the current iterated vector of the triangle span vectors, to check the condition.
					// s = (b2 * off1 - b1 * off2 - b2 * x + b1 * y) / (a2 * b1 - a1 * b2)
					// t = (-a2 * off1 + a1 * off2 + a2 * x - a1 * y) / (a2 * b1 - a1 * b2)
					
					// Precompute a part of the numerator and the divisor fraction.
					float denominator = (a2 * b1 - a1 * b2);
					float divisor;
					
					if (denominator != 0)
						divisor = 1 / denominator;
					else
						divisor = 0;

					int preS = b2 * off1 - b1 * off2 - b2 * x;
					int preT = -a2 * off1 + a1 * off2 + a2 * x;
					
					for (int y = rectBoundYT; y <= rectBoundYB; y++)
					{
						// Get vector decomposition.
						float s = (preS + b1 * y) * divisor;
						float t = (preT - a1 * y) * divisor;

						// Get the z-value.
						float cz = offz + za * s + zb * t;


						if (s >= 0.0f && t >= 0.0f && s + t <= 1.0f &&
							cz >= clipnear && cz <= clipfar)
						{
							if (zBuffer[x + (target->Height - y - 1) * target->Width] >= cz)
							{
								// Fill point, lays inside triangle.
								target->Pixels[x + (target->Height - y - 1) * target->Width].Char = '#';
								target->Pixels[x + (target->Height - y - 1) * target->Width].Color = colormap[i];
								zBuffer[x + (target->Height - y - 1) * target->Width] = cz;
							}
						}				
					}
				}
			}

			break;
	}

	return true;
}
