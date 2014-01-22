#include "modelloader_obj.h"

#define WAVEFRONT_MAX_NAMELEN 50

#define IS_CHAR_NUMERIC(expr) (expr == '-' || expr == '0' || expr == '1' || expr == '2' || expr == '3' || expr == '4' || expr == '5' || expr == '6' || expr == '7' || expr == '8' || expr == '9')

// Loads a Wavefront OBJ from stream.
struct List LoadWavefront(FILE* file, enum TE3D_VectorFormat format)
{
	struct List modellist = List_New(sizeof(struct TE3D_Model4f));
	
	char prefix = 0;
	char name[50];

	enum ConsoleColor defaultcolor = CONSOLECOLOR_DEFAULT;

	struct TE3D_Model4f model;
	struct TE3D_Vector4f vector;

	bool modelcreated = false;

	int iseof;


	while (iseof != EOF)
	{

		// Read prefix character.
		iseof = fscanf(file, "%c", &prefix);

		if (prefix == '#')
		{
			// Comment

			while(fgetc(file) != '\n') {}
		}
		else if(prefix == 'o')
		{
			// Object

			if (modelcreated)
				// Model already created, append to list.
				List_Add (&modellist, &model);
			
			model = TE3D_Model4f_New(format);
			modelcreated = true;
			iseof = fscanf(file, "%50", name);
			TE3D_Model4f_SetName(&model, name);
		}
		else if (prefix == 'v')
		{
			// Vector

			fscanf(file, "%f %f %f", &vector.x, &vector.y, &vector.z);
			// If we hit another 'v' a new vector starts and w defaults.
			iseof = fscanf(file, "%c", &prefix);

			vector.w = 1.0f;
			
			fseek(file, -1, SEEK_CUR);
			
			if (IS_CHAR_NUMERIC(prefix))
				iseof = fscanf(file, "%f", &vector.w);
			

			// At least at the vector to the model...
			ArrayList_Add(&model.Vectors, &vector);
			// and set default color, because MTL (Material Template Library) is not supported.
			ArrayList_Add(&model.Colors, &defaultcolor);

		}
		else if (prefix == 'f')
		{
			// Face

			// TE3D_VECTORFORMAT_POINTS ignores faces.
			switch (format)
			{
				case TE3D_VECTORFORMAT_LINES:
					TE3D_VectorIndex2 indexitem;
					int facecount = 0;
					int firstindex;

					fscanf(file, "%d %d", &indexitem.i1, &indexitem.i2);
					firstindex = indexitem.i1;

					ArrayList_Add(&model.Indices, &indexitem);

					// If other face-indices follow, re-scanf.
					while (true)
					{
						iseof = fscanf(file, "%c", &prefix);
						fseek(file, -1, SEEK_CUR);

						if (IS_CHAR_NUMERIC(prefix))
						{
							indexitem.i1 = indexitem.i2;
							iseof = fscanf(file, "%f", &indexitem.i2);

							// Add the line to the model.
							ArrayList_Add(&model.Indices, &indexitem);

							facecount++;
						}
						else
							break;
					}

					if (facecount != 0)
					{
						// Add closing line.
						indexitem.i1 = firstindex;	
						ArrayList_Add(&model.Indices, &indexitem);
					}

					break;

				case TE3D_VECTORFORMAT_TRIANGLES:
					//fscanf(file, "%d %d %d", &face1, &face2, &face3);
					break;
			}
		}
		else
		{
			// Goto next line.
			while(fgetc(file) != '\n') {}
		}
	

	}
	
	if (modelcreated)
		// Add the last model to the list.
		List_Add(&modellist, &model);

	return modellist;
}

// Loads a Wavefront OBJ from file.
struct List LoadWavefrontFromFile(char* path, enum TE3D_VectorFormat format)
{
	FILE* file = fopen(path, "r");
	return LoadWavefront(file, format);
	fclose(file);
}