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

#pragma once

#include "transformation.h"
#include "models.h"
#include "list.h"

#include <stdio.h>
#include <math.h>

// Contains the available illumination modes for an MTL-Material.
typedef enum
{
	ColorOnAmbientOff = 0,
	ColorOnAmbientOn = 1,
	HighlightOn = 2,
	ReflectionOnRaytraceOn = 3,
	Transparency_GlassOnRaytrayceOn = 4,
	Reflection_FresnelOnRaytraceOn = 5,
	Transparency_RefractionOn_Reflection_FresnelOffRaytraceOn = 6,
	Transparency_RefractionOn_Reflection_FresnelOnRaytraceOn = 7,
	ReflectionOnRaytraceOff = 8,
	Transparency_GlassOn_Reflection_RaytraceOff = 9,
	CastShadowsOntoInvisibleSurfaces = 10
} MTLIllumination;

#define MTLILLUMINATION_COLOR_ON_AMBIENT_OFF (MTLIllumination)0
#define MTLILLUMINATION_COLOR_ON_AMBIENT_ON (MTLIllumination)1
#define MTLILLUMINATION_HIGHLIGHT_ON (MTLIllumination)2
#define MTLILLUMINATION_REFLECTION_ON_RAYTRACE_ON (MTLIllumination)3
#define MTLILLUMINATION_TRANSPARENCY_GLASS_ON_RAYTRACE_ON (MTLIllumination)4
#define MTLILLUMINATION_REFLECTION_FRESNEL_ON_RAYTRACE_ON (MTLIllumination)5
#define MTLILLUMINATION_TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_OFF_RAYTRACE_ON (MTLIllumination)6
#define MTLILLUMINATION_TRANSPARENCY_REFRACTION_ON_REFLECTION_FRESNEL_ON_RAYTRACE_ON (MTLIllumination)7
#define MTLILLUMINATION_REFLECTION_ON_RAYTRACE_OFF (MTLIllumination)8
#define MTLILLUMINATION_TRANSPARENCY_GLASS_ON_REFLECTION_RAYTRACE_OFF (MTLIllumination)9
#define MTLILLUMINATION_CAST_SHADOWS_ONTO_INVISIBLE_SURFACES (MTLIllumination)10



#define WAVEFRONT_MTL_MAX_ID 63
// Describes an MTL-Material.
typedef struct
{
	// The name/ID of the material.
	char ID[WAVEFRONT_MTL_MAX_ID + 1];
	// The diffuse color.
	float diffuse[3];
	// The ambient color.
	float ambient[3];
	// The specular color.
	float specular[3];
	// The specular coefficient.
	float specular_coeff;
	// The transparency factor.
	float transparent;
	// The optical density.
	float optical_density;
	// The illumination mode.
	MTLIllumination illum;
} MTLMaterial;



// Loads a Wavefront OBJ from stream.
// file: The stream to load the data from.
// format: The format the vectors should have inside the model.
//		   Note: If TE3D_VECTORFORMAT_PIXELS or TE3D_VECTORFORMAT_LINES is specified, the faces of the wavefront file are automatically converted.
// vectorscount: The number of vertices loaded.
// indicescount: The number of indices loaded. When TE3D_VECTORFORMAT_PIXELS is specified, this parameter should be NULL.
List LoadWavefront(FILE* file, TE3D_VectorFormat format,
				   int* vectorscount, int* indicescount);

// Loads a Wavefront OBJ from file.
// path: The path of the file.
// format: The format the vectors should have inside the model.
//		   Note: If TE3D_VECTORFORMAT_PIXELS or TE3D_VECTORFORMAT_LINES is specified, the faces of the wavefront file are automatically converted.
// vectorscount: The number of vertices loaded.
// indicescount: The number of indices loaded. When TE3D_VECTORFORMAT_PIXELS is specified, this parameter should be NULL.
List LoadWavefrontFromFile(char* path, TE3D_VectorFormat format,
						   int* vectorscount, int* indicescount);

// Loads an MTL-file (Material Template Library).
// file: The stream to load the materials from.
List LoadMTL(FILE* file);

// Loads an MTL-file (Material Template Library).
// path: The path of the file to load materials from.
List LoadMTLFromFile(char* path);