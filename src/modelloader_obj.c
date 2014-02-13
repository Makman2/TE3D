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

#include "modelloader_obj.h"

#define WAVEFRONT_MAX_NAMELEN 63
#define STRINGIZE(x) #x
#define STRINGIZE_EXPAND(x) STRINGIZE(x)

// FIXME I think there is a std macro for this
// and I think an inline function would do better - try IS_CHAR_NUMERIC(i++)
// i will be incremented three times
#define IS_CHAR_NUMERIC(expr) ((expr) == '-' || ((expr) >= '0' && (expr) <= '9'))

// Loads a Wavefront OBJ from stream.
List LoadWavefront(FILE* file, TE3D_VectorFormat format, int* vectorscount, int* indicescount)
{
	List modellist = List_New(sizeof(TE3D_Model4f));
	
	// Manage an array of strings and the corresponding files.
	List MTLs = List_New(sizeof(MTLMaterial));
	
	char prefix = 0;
	char name[WAVEFRONT_MAX_NAMELEN + 1];

	char mtlID[WAVEFRONT_MTL_MAX_ID + 1];
	ConsoleColor mtlcolor = CONSOLECOLOR_DEFAULT;

	TE3D_Model4f model;
	TE3D_Vector4f vector;

	bool modelcreated = false;

	int iseof = !EOF;
	
	// Reset count parameters.
	*vectorscount = 0;
	*indicescount = 0;

	while (iseof != EOF)
	{

		// Read prefix character.
		iseof = fscanf(file, " %c", &prefix);

		if (prefix == '#')
		{
			// Comment

			iseof = fgetc(file);
			while(iseof != '\n' && iseof != -1)
			{
				iseof = fgetc(file);
			}
		}
		else if (prefix == 'm')
		{
			fscanf(file, "%5s", name);
			if (strcmp(name, "tllib") == 0)
			{
				// MTL library import.
				// Use 'name' as placeholder.
				fscanf(file, "%" STRINGIZE_EXPAND(WAVEFRONT_MAX_NAMELEN) "s", name);
				
				// Append materials to current list.
				List fileMTLs = LoadMTLFromFile(name);
				for(int i = 0; i < fileMTLs.count; i++)
				{
					List_Add(&MTLs, List_At(&fileMTLs, i));
				}
				List_Release(&fileMTLs);
			}
		}
		else if (prefix == 'u')
		{
			fscanf(file, "%5s", name);
			if (strcmp(name, "semtl") == 0)
			{
				// MTL material usage.
				fscanf(file, "%" STRINGIZE_EXPAND(WAVEFRONT_MTL_MAX_ID) "s", mtlID);
				int index = -1;

				// Search for material in current imported MTL-materials.
				for (int i = 0; i < MTLs.count; i++)
				{
					if (strcmp(mtlID, ((MTLMaterial*)List_At(&MTLs, i))->ID) == 0)
					{
						index = i;
						break;
					}
				}

				if (index == -1)
				{
					// Material not found.
					mtlcolor = CONSOLECOLOR_DEFAULT;
				}
				else
				{
					// Material found.
					// Using diffuse color for console color interpolation.
					((MTLMaterial*)List_At(&MTLs, index))->diffuse;
					
////// ################# MAKE HER THE COLOR CONVERTER ############### ///////////////////

				}
			}
		}
		else if (prefix == 'o')
		{
			// Object

			if (modelcreated)
			{
				// Model already created, append to list...
				List_Add (&modellist, &model);
				// and update count parameters.
				*vectorscount += model.Vectors.count;
				*indicescount += model.Indices.count;
			}
			
			model = TE3D_Model4f_New(format);
			modelcreated = true;
			iseof = fscanf(file, "%" STRINGIZE_EXPAND(WAVEFRONT_MAX_NAMELEN) "s", name);
			TE3D_Model4f_SetName(&model, name);
		}
		else if (prefix == 'v')
		{
			// Vector
			fscanf(file, "%f %f %f", &vector.x, &vector.y, &vector.z);
			// If we hit another 'v' a new vector starts and w defaults.
			iseof = fscanf(file, " %c", &prefix);

			vector.w = 1.0f;
			
			fseek(file, -1, SEEK_CUR);
			
			if (iseof != EOF && IS_CHAR_NUMERIC(prefix))
				iseof = fscanf(file, "%f", &vector.w);
			

			// At least at the vector to the model...
			ArrayList_Add(&model.Vectors, &vector);

			if (format == TE3D_VECTORFORMAT_POINTS)
				// and set default color, because MTL (Material Template Library) is not supported.
				ArrayList_Add(&model.Colors, &mtlcolor);
		}
		else if (prefix == 'f')
		{
			// Face

			switch (format)
			{
				case TE3D_VECTORFORMAT_POINTS:
					// TE3D_VECTORFORMAT_POINTS ignores faces.
					break;
			
				case TE3D_VECTORFORMAT_LINES:
				{	
					TE3D_VectorIndex2 indexitem;
					int facecount = 0;
					int firstindex;

					fscanf(file, "%d %d", &indexitem.i1, &indexitem.i2);
					
					indexitem.i1 -= *vectorscount + 1;
					indexitem.i2 -= *vectorscount + 1;
					
					firstindex = indexitem.i1;
					
					ArrayList_Add(&model.Indices, &indexitem);

					
					// Add color because now they are index-assigned, not vertex-assigned.
					ArrayList_Add(&model.Colors, &mtlcolor);

					// If other face-indices follow, re-scanf.
					while (iseof != EOF)
					{
						iseof = fscanf(file, " %c", &prefix);
						fseek(file, -1, SEEK_CUR);

						if (iseof == EOF)
							break;

						if (IS_CHAR_NUMERIC(prefix))
						{
							indexitem.i1 = indexitem.i2;
							iseof = fscanf(file, "%d", &indexitem.i2);

							indexitem.i2 -= *vectorscount + 1;

							// Add the line to the model.
							ArrayList_Add(&model.Indices, &indexitem);

							// And add again.
							ArrayList_Add(&model.Colors, &mtlcolor);

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
				}

				case TE3D_VECTORFORMAT_TRIANGLES:
					//fscanf(file, "%d %d %d", &face1, &face2, &face3);
					break;
			}
		}
		else
		{
			// Goto next line.
			iseof = fgetc(file);
			while(iseof != '\n' && iseof != -1)
			{
				iseof = fgetc(file);
			}
		}
	

	}
	
	if (modelcreated)
	{
		// Add the last model to the list...
		List_Add(&modellist, &model);
		// and update count parameters.
		*vectorscount += model.Vectors.count;
		*indicescount += model.Indices.count;
	}


	List_Release(&MTLs);

	return modellist;
}

// Loads a Wavefront OBJ from file.
List LoadWavefrontFromFile(char* path, TE3D_VectorFormat format, int* vectorscount, int* indicescount)
{
	FILE* file = fopen(path, "r");
	List returnlist = LoadWavefront(file, format, vectorscount, indicescount);
	fclose(file);
	return returnlist;
}


// Loads an MTL-file (Material Template Library).
List LoadMTL(FILE* file)
{
	List materials = List_New(sizeof(MTLMaterial));
	
	char prefix = 0;
	char name[WAVEFRONT_MTL_MAX_ID + 1];

	int iseof = !EOF;
	
	while (iseof != EOF)
	{
		// Read prefix character.
		iseof = fscanf(file, " %c", &prefix);

		if (prefix == '#')
		{
			// Comment

			iseof = fgetc(file);
			while(iseof != '\n' && iseof != -1)
			{
				iseof = fgetc(file);
			}
		}
		else if (prefix == 'n')
		{
			fscanf(file, "%5s", name);
			if (strcmp(name, "ewmtl") == 0)
			{
				// Read the material name/id.
				iseof = fscanf(file, "%" STRINGIZE_EXPAND(WAVEFRONT_MTL_MAX_ID) "s", name);
				
				MTLMaterial newmaterial;
				newmaterial.diffuse[0] = 0.0f;
				newmaterial.diffuse[1] = 0.0f;
				newmaterial.diffuse[2] = 0.0f;
				newmaterial.ambient[0] = 0.0f;
				newmaterial.ambient[1] = 0.0f;
				newmaterial.ambient[2] = 0.0f;
				newmaterial.specular[0] = 0.0f;
				newmaterial.specular[1] = 0.0f;
				newmaterial.specular[2] = 0.0f;
				newmaterial.specular_coeff = 0.0f;
				newmaterial.transparent = 1.0f;
				newmaterial.optical_density = 0.0f;
				newmaterial.illum = MTLILLUMINATION_COLOR_ON_AMBIENT_OFF;

				strcpy(newmaterial.ID, name);


				// Proceed reading the material values.
				while (iseof != EOF)
				{
					iseof = fscanf(file, "%6s", name);
					if (strcmp(name, "Ns") == 0)
					{
						// specular coefficient
						iseof = fscanf(file, "%f", &newmaterial.specular_coeff);
					}
					else if (strcmp(name, "Ka") == 0)
					{
						// ambient color
						iseof = fscanf(file, "%f %f %f", &newmaterial.ambient[0], &newmaterial.ambient[1], &newmaterial.ambient[2]);
					}
					else if (strcmp(name, "Kd") == 0)
					{
						// diffuse color
						iseof = fscanf(file, "%f %f %f", &newmaterial.diffuse[0], &newmaterial.diffuse[1], &newmaterial.diffuse[2]);
					}
					else if (strcmp(name, "Ks") == 0)
					{
						// specular color
						iseof = fscanf(file, "%f %f %f", &newmaterial.specular[0], &newmaterial.specular[1], &newmaterial.specular[2]);
					}
					else if (strcmp(name, "Ni") == 0)
					{
						// optical density
						iseof = fscanf(file, "%f", &newmaterial.optical_density);
					}
					else if (strcmp(name, "d") == 0)
					{
						// transparency	
						iseof = fscanf(file, "%f", &newmaterial.transparent);
					}
					else if (strcmp(name, "illum") == 0)
					{
						// illumination mode
						int illummode;
						iseof = fscanf(file, "%d", &illummode);
						if (illummode > 10 || illummode < 0)
							// Invalid illumination mode, set to standard.
							newmaterial.illum = MTLILLUMINATION_COLOR_ON_AMBIENT_OFF;
						else
							newmaterial.illum = (MTLIllumination)illummode;
					}
					else if (strcmp(name, "newmtl") == 0)
					{
						// No other value: add to the material list, reset cursor and goto next material.
						if (iseof != EOF)
							fseek(file, -6, SEEK_CUR);
						goto MATERIAL_END;
					}
					else
					{
						// Unknown command (or comment), overread line.
						iseof = fgetc(file);
						while(iseof != '\n' && iseof != -1)
						{
							iseof = fgetc(file);
						}
					}


				}

				MATERIAL_END:

				List_Add(&materials, &newmaterial);
			}
		}

	}

	return materials;
}

// Loads an MTL-file (Material Template Library).
List LoadMTLFromFile(char* path)
{
	FILE* file = fopen(path, "r");
	List returnlist = LoadMTL(file);
	fclose(file);
	return returnlist;
}