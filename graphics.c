#include "graphics.h"

#include <stdlib.h>
#include <math.h>
#ifndef WIN32
		#include <stdbool.h>
#endif

// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
// plane: A normal vector, that defines the plane to project on.
// worldsup: A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjection(TE3D_Vector3f plane, TE3D_Vector3f worldsup)
{
	// The transformation matrix.
    TE3D_Matrix4x4f result;
    // The ortho-normal span-vectors of the plane.
    TE3D_Vector3f xvec, yvec;

    // Normalize plane vector.
    TE3D_Vector3f_normalize(&plane);

    // Gram-Schmidting the worldsup-vector to get the first span-vector.
    xvec = TE3D_Vector3f_sub(worldsup, TE3D_Vector3f_project(worldsup, plane));
    yvec = TE3D_Vector3f_cross(plane, xvec);

    double normx = TE3D_Vector3f_mul(xvec * xvec);
    double normy = TE3D_Vector3f_mul(yvec * yvec);

    result.m11 = xvec.x / normx;
    result.m12 = xvec.y / normx;
    result.m13 = xvec.z / normx;
    result.m14 = 0;
	result.m21 = yvec.x / normy;
    result.m22 = yvec.y / normy;
    result.m23 = yvec.z / normy;
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 0;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	
    return result;
}
TE3D_Matrix3x3f TE3D_Transformation3x3f_OrthogonalProjection(TE3D_Vector3f plane, TE3D_Vector3f worldsup)
{
	// The transformation matrix.
    TE3D_Matrix3x3f result;
    // The ortho-normal span-vectors of the plane.
    TE3D_Vector3f xvec, yvec;

    // Normalize plane vector.
    TE3D_Vector3f_normalize(&plane);

    // Gram-Schmidting the worldsup-vector to get the first span-vector.
    xvec = TE3D_Vector3f_sub(worldsup, TE3D_Vector3f_project(worldsup, plane));
    yvec = TE3D_Vector3f_cross(plane, xvec);

    double normx = TE3D_Vector3f_mul(xvec * xvec);
    double normy = TE3D_Vector3f_mul(yvec * yvec);

    result.m11 = xvec.x / normx;
    result.m12 = xvec.y / normx;
    result.m13 = xvec.z / normx;
	result.m21 = yvec.x / normy;
    result.m22 = yvec.y / normy;
    result.m23 = yvec.z / normy;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 0;
	
    return result;
}

// Creates a matrix that describes a translation.
// shiftX: The shift of the x-component.
// shiftY: The shift of the y-component.
// shiftZ: The shift of the z-component.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Translation(float shiftX, float shiftY, float shiftZ)
{
	TE3D_Matrix4x4f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m13 = 0;
	result.m14 = shiftX;
	result.m21 = 0;
	result.m22 = 1;
	result.m23 = 0;
	result.m24 = shiftY;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 1;
	result.m34 = shiftZ;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}
// Creates a matrix that describes a translation in 2D.
// shiftX: The shift of the x-component.
// shiftY: The shift of the y-component.
TE3D_Matrix3x3f TE3D_Transformation3x3f_Translation(float shiftX, float shiftY)
{
	TE3D_Matrix3x3f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m13 = 0;
	result.m21 = 0;
	result.m22 = 1;
	result.m23 = 0;
	result.m31 = shiftX;
	result.m32 = shiftY;
	result.m33 = 1;
	return result;
}


// Creates a matrix that describes a scale.
// scaleX: The scale of the x-component.
// scaleY: The scale of the y-component.
// scaleZ: The scale of the z-component.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Scale(float scaleX, float scaleY, float scaleZ)
{
	TE3D_Matrix4x4f result;
	result.m11 = scaleX;
	result.m12 = 0;
	result.m13 = 0;
	result.m14 = 0;
	result.m21 = 0;
	result.m22 = scaleY;
	result.m23 = 0;
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = scaleZ;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}
TE3D_Matrix3x3f TE3D_Transformation3x3f_Scale(float scaleX, float scaleY, float scaleZ)
{
	TE3D_Matrix3x3f result;
	result.m11 = scaleX;
	result.m12 = 0;
	result.m13 = 0;
	result.m21 = 0;
	result.m22 = scaleY;
	result.m23 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = scaleZ;
	return result;
}

// Creates the identity matrix.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Identity()
{
	TE3D_Matrix4x4f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m13 = 0;
	result.m14 = 0;
	result.m21 = 0;
	result.m22 = 1;
	result.m23 = 0;
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 1;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}
TE3D_Matrix3x3f TE3D_Transformation3x3f_Identity()
{
	TE3D_Matrix3x3f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m13 = 0;
	result.m21 = 0;
	result.m22 = 1;
	result.m23 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 1;
	return result;
}
TE3D_Matrix2x2f TE3D_Transformation2x2f_Identity()
{
	TE3D_Matrix2x2f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m21 = 0;
	result.m22 = 1;
	return result;
}

// Creates a rotation matrix for any axis.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Rotate(TE3D_Vector3f axis, TE3D_Vector3f offset, double angle)
{
	TE3D_Vector3f_normalize(&axis);
	
	TE3D_Matrix4x4f result;
	result.m11 = axis.x * axis.x * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m12 = axis.x * axis.y * (1 - (float)cos(angle)) - axis.z * (float)sin(angle);
	result.m13 = axis.x * axis.z * (1 - (float)cos(angle)) + axis.y * (float)sin(angle);
	result.m14 = offset.x - ((float)cos(angle) + (1 - (float)cos(angle)) * axis.x * axis.x) * offset.x - ((1 - (float)cos(angle)) * axis.x * axis.y - (float)sin(angle) * axis.z) * offset.y - ((float)sin(angle) * axis.y + (1 - (float)cos(angle)) * axis.x * axis.z) * offset.z;
	result.m21 = axis.x * axis.y * (1 - (float)cos(angle)) + axis.z * (float)sin((float)angle);
	result.m22 = axis.y * axis.y * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m23 = axis.y * axis.z * (1 - (float)cos(angle)) - axis.x * (float)sin(angle);
	result.m24 = -((1 - (float)cos(angle)) * axis.x * axis.y + (float)sin(angle) * axis.z) * offset.x + offset.y - ((float)cos(angle) + (1 - (float)cos(angle)) * axis.y * axis.y) * offset.y - (-(float)sin(angle) * axis.x + (1 - (float)cos(angle)) * axis.y * axis.z) * offset.z;
	result.m31 = axis.x * axis.z * (1 - (float)cos(angle)) - axis.y * (float)sin(angle);
	result.m32 = axis.y * axis.z * (1 - (float)cos(angle)) + axis.x * (float)sin(angle);
	result.m33 = axis.z * axis.z * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m34 = -(-(float)sin(angle) * axis.y + (1 - (float)cos(angle)) * axis.x * axis.z) * offset.x - ((float)sin(angle) * axis.x + (1 - (float)cos(angle)) * axis.y * axis.z) * offset.y + offset.z - ((float)cos(angle) + (1 - (float)cos(angle)) * axis.z * axis.z) * offset.z;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}

// Create a rotation matrix for any axis through the origin.
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateOrigin(TE3D_Vector3f axis, double angle)
{
	TE3D_Vector3f_normalize(&axis);

	TE3D_Matrix4x4f result;
	result.m11 = axis.x * axis.x * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m12 = axis.x * axis.y * (1 - (float)cos(angle)) - axis.z * (float)sin(angle);
	result.m13 = axis.x * axis.z * (1 - (float)cos(angle)) + axis.y * (float)sin(angle);
	result.m14 = 0;
	result.m21 = axis.x * axis.y * (1 - (float)cos(angle)) + axis.z * (float)sin((float)angle);
	result.m22 = axis.y * axis.y * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m23 = axis.y * axis.z * (1 - (float)cos(angle)) - axis.x * (float)sin(angle);
	result.m24 = 0;
	result.m31 = axis.x * axis.z * (1 - (float)cos(angle)) - axis.y * (float)sin(angle);
	result.m32 = axis.y * axis.z * (1 - (float)cos(angle)) + axis.x * (float)sin(angle);
	result.m33 = axis.z * axis.z * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}

// Creates a rotation matrix (for x-axis rotation).
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateX(double angle)
{
	TE3D_Matrix4x4f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m13 = 0;
	result.m14 = 0;
	result.m21 = 0;
	result.m22 = (float)cos(angle);
	result.m23 = -(float)sin(angle);
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = (float)sin(angle);
	result.m33 = (float)cos(angle);
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}

// Creates a rotation matrix (for y-axis rotation).
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateY(double angle)
{
	TE3D_Matrix4x4f result;
	result.m11 = (float)cos(angle);
	result.m12 = 0;
	result.m13 = (float)sin(angle);
	result.m14 = 0;
	result.m21 = 1;
	result.m22 = 0;
	result.m23 = 0;
	result.m24 = 0;
	result.m31 = -(float)sin(angle);
	result.m32 = 0;
	result.m33 = (float)cos(angle);
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}

// Creates a rotation matrix (for z-axis rotation).
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateZ(double angle)
{
	TE3D_Matrix4x4f result;
	result.m11 = (float)cos(angle);
	result.m12 = -(float)sin(angle);
	result.m13 = 0;
	result.m14 = 0;
	result.m21 = (float)sin(angle);
	result.m22 = (float)cos(angle);
	result.m23 = 0;
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 1;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	return result;
}

// Creates a rotation matrix (for x-axis rotation).
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateX(double angle)
{
	TE3D_Matrix3x3f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m13 = 0;
	result.m21 = 0;
	result.m22 = (float)cos(angle);
	result.m23 = -(float)sin(angle);
	result.m31 = 0;
	result.m32 = (float)sin(angle);
	result.m33 = (float)cos(angle);
	return result;
}
// Creates a rotation matrix (for y-axis rotation).
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateY(double angle)
{
	TE3D_Matrix3x3f result;
	result.m11 = (float)cos(angle);
	result.m12 = 0;
	result.m13 = (float)sin(angle);
	result.m21 = 1;
	result.m22 = 0;
	result.m23 = 0;
	result.m31 = -(float)sin(angle);
	result.m32 = 0;
	result.m33 = (float)cos(angle);
	return result;
}
// Creates a rotation matrix (for z-axis rotation).
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateZ(double angle)
{
	TE3D_Matrix3x3f result;
	result.m11 = (float)cos(angle);
	result.m12 = -(float)sin(angle);
	result.m13 = 0;
	result.m21 = (float)sin(angle);
	result.m22 = (float)cos(angle);
	result.m23 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 1;
	return result;	
}
// Creates a rotation matrix (for z-axis rotation).
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateOrigin(TE3D_Vector3f axis, double angle)
{
	TE3D_Vector3f_normalize(&axis);
	
	TE3D_Matrix3x3f result;
	result.m11 = axis.x * axis.x * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m12 = axis.x * axis.y * (1 - (float)cos(angle)) - axis.z * (float)sin(angle);
	result.m13 = axis.x * axis.z * (1 - (float)cos(angle)) + axis.y * (float)sin(angle);
	result.m21 = axis.x * axis.y * (1 - (float)cos(angle)) + axis.z * (float)sin((float)angle);
	result.m22 = axis.y * axis.y * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m23 = axis.y * axis.z * (1 - (float)cos(angle)) - axis.x * (float)sin(angle);
	result.m31 = axis.x * axis.z * (1 - (float)cos(angle)) - axis.y * (float)sin(angle);
	result.m32 = axis.y * axis.z * (1 - (float)cos(angle)) + axis.x * (float)sin(angle);
	result.m33 = axis.z * axis.z * (1 - (float)cos(angle)) + (float)cos(angle);
	return result;
}

// Creates a rotation matrix in 2D-space for any axis through the origin.
TE3D_Matrix2x2f TE3D_Transformation2x2f_RotateOrigin(double angle)
{	
	TE3D_Matrix2x2f result;
	result.m11 = (float)cos(angle);
	result.m12 = -(float)sin(angle);
	result.m21 = (float)sin(angle);
	result.m22 = (float)cos(angle);
	return result;	
}
// Creates a rotation matrix in 2D-space for any axis.
// offset: The offset of the rotation axis.
// angle: The angle.
TE3D_Matrix3x3f TE3D_Transformation3x3f_Rotate(TE3D_Vector3f offset, double angle)
{
	TE3D_Matrix3x3f result;
	result.m11 = (float)cos(angle);
	result.m12 = 0;
	result.m13 = offset.x * (-(float)cos(angle) * offset.x + (float)sin(angle) * offset.y);
	result.m21 = 0;
	result.m22 = (float)cos(angle);
	result.m23 = offset.y * (-(float)sin(angle) * offset.x - (float)cos(angle) * offset.y);
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 1;
	return result;
}




// Creates a char surface.
// Width: The width of the surface.
// Returns the newly created surface.
struct TE3D_Surface* TE3D_CreateSurface(int width, int height)
{
	// Allocate memory for "char-pixels" and surface and zero-initialize it.
	char* addr = calloc(sizeof(struct TE3D_Surface) + sizeof(struct TE3D_ColorChar) * width * height);
	
	// Initialize surface.
	TE3D_Surface* surface = addr;
	(*surface).Width = width;
	(*surface).Height = height;
	(*surface).Stride = sizeof(struct TE3D_ColorChar) * width;
	// Point to the area after the structure.
	(*surface).Pixels = addr + sizeof(surface);
	
	return surface;	
}

// Releases a char surface.
// surface: The surface to release.
void TE3D_ReleaseSurface(struct TE3D_Surface* surface)
{
	free(surface);
	
	// Reset struct values.
	(*surface).Width = 0;
	(*surface).Height = 0;
	(*surface).Stride = 0;
	(*surface).Pixels = NULL;
}