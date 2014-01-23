#include "ascii_converter.h"

#ifndef INFINITY
	#define INFINITY (1.0 / 0.0)
#endif


static void memsetd(double* dst, double value, int count)
{
	for (int i = 0; i < count; i++)
	{
		(*dst) = value;
		dst++;
	}
}

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
/* target = x ebene; v1 und v2 als vektoren; cos alpha (v1,v2) =  a_x/ax²+ay² ;  

			   45° = /\
		   0°,180° = _
			   90° = |		*/

			for (int i = 0; i < count; i++  )

			{
				int xround = (int)round(vectors[i].x);
				int yround = (int)round(vectors[i].y);
		

				if (zBuffer[xround + yround *target->Width] >= vectors[i].z &&

					xround >= 0 && xround < target -> Width &&
					yround >= 0 && yround < target ->Height)
				{


					zBuffer[xround + yround * target ->Width] = vectors[i].z;
					target->Pixels[xround + yround * target ->Width].Char = '_';
					target->Pixels[xround + yround * target ->Width].Char = '/\|'];


		
			}




			// -- Also hier dasselbe mit dem Zeichnen, nur eben keine Punkte sondern Linien. Jetzt ist 'indices' nicht mehr NULL, sondern ein Zeiger auf
			// -- ein Array von integern (also Ganzzahlen), die die Indexe beschreiben. D.h. Die Indexe sagen dir, welche Linien aus dem vectors-Array
			// -- verbunden werden sollen.

			break;

		case TE3D_VECTORFORMAT_TRIANGLES:
			// Triangle connections.
			// If indices is again NULL the function must also exit.
			if (!indices)
				return false;

			// -- Dasselbe hier wie oben nur jetzt mit Dreiecken malen und indices ist vom Typ Array von TE3D_VectorIndex3.

			break;
	}

	// -- Wenn alles geklappt hat, 'true' zurückgeben.
	// -- PS: Alle deutschen Kommentare (mit -- nach jedem //) werden am Ende gelöscht wenn die Funktion fertig ist.
	return true;
}
