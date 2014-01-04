#pragma once

#include <math.h>

// Describes a 4-dimensional vector.
struct TE3D_Vector4f
{
	float x, y, z, w;
}


// Describes a 3 Dimensional Vector
struct TE3D_Vector3f{
	float x;
	float y;
	float z;
};

// Describes a 2-dimensional vector.
struct TE3D_Vector2f
{
	float x, y;
}

// Describes a 3x2 matrix.
struct TE3D_Matrix3x2f
{
	float m11, m12, m13, m21, m22, m23;
}

// Describes a 3x3 matrix.
struct TE3D_Matrix3x3f
{
	float m11, m12, m13, m21, m22, m23, m31, m32, m33;
}

struct TE3D_Matrix4x4f
{
	float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
}

struct TE3D_Pixel{
	int r;
	int g;
	int b;

};

// Some vector functions.

// Returns a new 3-dimensional vector with predefined values.
inline TE3D_Vector3f_N(float x, float y, float z)
{
	TE3D_Vector3f result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

// Returns scalar-product of two vectors.
inline double TE3D_Vector3f_mul(TE3D_Vector3f v1, TE3D_Vector3f v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Multiplicates a vector with a scalar.
inline TE3D_Vector3f TE3D_Vector3f_muls(TE3D_Vector3f vector, float scalar)
{
	TE3D_Vector3f result;
	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	return result;
}

// Divides a vector with a scalar.
inline TE3D_Vector3f TE3D_Vector3f_div(TE3D_Vector3f vector, float scalar)
{
	TE3D_Vector3f result;
	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	result.z = vector.z / scalar;
	return result;
}

// Add two vectors.
inline TE3D_Vector3f TE3D_Vector3f_add(TE3D_Vector3f v1, TE3D_Vector3f v2)
{
	TE3D_Vector3f result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

// Subtract two vectors.
inline TE3D_Vector3f TE3D_Vector3f_sub(TE3D_Vector3f v1, TE3D_Vector3f v2)
{
	TE3D_Vector3f result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

// Returns the cross-product of two 3-dimensional vectors.
inline TE3D_Vector3f TE3D_Vector3f_cross(TE3D_Vector3f v1, TE3D_Vector3f v2)
{
	TE3D_Vector3f result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

// Normalizes the given vector.
inline void TE3D_Vector3f_normalize(TE3D_Vector3f* vector)
{
	float norm = sqrt(TE3D_Vector3f_mul(vector, vector));
	vector->x /= norm;
	vector->y /= norm;
	vector->z /= norm;
}

// Returns the projection of a vector on another vector.
inline TE3D_Vector3f TE3D_Vector3f_project(TE3D_Vector3f vector, TE3D_Vector3f projectOn)
{
	return TE3D_Vector3f_muls(projectOn, (TE3D_Vector3f_mul(vector, projectOn) / TE3D_Vector3f_mul(projectOn, projectOn)));
}


// Returns a new 2-dimensional vector with predefined values.
inline TE3D_Vector2f_N(float x, float y)
{
	TE3D_Vector2f result;
	result.x = x;
	result.y = y;
	return result;
}

// Returns scalar-product of two vectors.
inline double TE3D_Vector2f_mul(TE3D_Vector2f v1, TE3D_Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// Multiplicates a vector with a scalar.
inline TE3D_Vector2f TE3D_Vector2f_muls(TE3D_Vector2f vector, float scalar)
{
	TE3D_Vector2f result;
	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	return result;
}

// Divides a vector with a scalar.
inline TE3D_Vector2f TE3D_Vector2f_div(TE3D_Vector2f vector, float scalar)
{
	TE3D_Vector2f result;
	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	return result;
}

// Add two vectors.
inline TE3D_Vector2f TE3D_Vector2f_add(TE3D_Vector2f v1, TE3D_Vector2f v2)
{
	TE3D_Vector2f result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return result;
}

// Subtract two vectors.
inline TE3D_Vector2f TE3D_Vector2f_sub(TE3D_Vector2f v1, TE3D_Vector2f v2)
{
	TE3D_Vector2f result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return result;
}

// Normalizes the given vector.
inline void TE3D_Vector2f_normalize(TE3D_Vector2f* vector)
{
	float norm = sqrt(TE3D_Vector2f_mul(vector, vector));
	vector->x /= norm;
	vector->y /= norm;
}

// Returns the projection of a vector on another vector.
inline TE3D_Vector2f TE3D_Vector2f_project(TE3D_Vector2f vector, TE3D_Vector2f projectOn)
{
	return TE3D_Vector2f_muls(projectOn, (TE3D_Vector2f_mul(vector, projectOn) / TE3D_Vector2f_mul(projectOn, projectOn)));
}


// Multiplicates a 3x2 matrix with a 3-dimensional vector.
inline TE3D_Vector2f TE3D_Matrix3x2f_mul3(TE3D_Matrix3x2f matrix, TE3D_Vector3f vector)
{
	TE3D_Vector2f result;
    result.x = matrix.m11 * vector.x + matrix.m12 * vector.y + matrix.m13 * vector.z;
    result.y = matrix.m21 * vector.x + matrix.m22 * vector.y + matrix.m23 * vector.z;
    return result;
}

// Multiplicates a 3x2 matrix with a 2-dimensional vector.
inline TE3D_Vector3f TE3D_Matrix3x2f_mul2(TE3D_Matrix3x2f matrix, TE3D_Vector2f vector)
{
	TE3D_Vector3f result;
    result.x = matrix.m11 * vector.x + matrix.m21 * vector.y;
    result.y = matrix.m12 * vector.x + matrix.m22 * vector.y;
	result.z = matrix.m13 * vector.x + matrix.m23 * vector.y;
    return result;
}


// Multiplicates a 3x3 matrix with a 3-dimensional vector.
inline TE3D_Vector3f TE3D_Matrix3x3f_mul3(TE3D_Matrix3x3f matrix, TE3D_Vector3f vector)
{
	TE3D_Vector3f result;
	result.x = vector.x * matrix.m11 + vector.y * matrix.m12 + vector.z * matrix.m13;
	result.x = vector.x * matrix.m21 + vector.y * matrix.m22 + vector.z * matrix.m23;
	result.x = vector.x * matrix.m31 + vector.y * matrix.m32 + vector.z * matrix.m33;
	return result;
}


// Zero-expands a 3x3 matrix to a 4x4 matrix.
inline TE3D_Matrix4x4f TE3D_Matrix3x3f_ExpandTo4x4(TE3D_Matrix3x3f matrix)
{
	TE3D_Matrix4x4f result;
	result.m11 = matrix.m11;
	result.m12 = matrix.m12;
	result.m13 = matrix.m13;
	result.m14 = 0;
	result.m21 = matrix.m21;
	result.m22 = matrix.m22;
	result.m23 = matrix.m23;
	result.m24 = 0;
	result.m31 = matrix.m31;
	result.m32 = matrix.m32;
	result.m33 = matrix.m33;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 0;
	return result;
}

// Zero-expands a 3x3 matrix to a 4x4 matrix.
inline TE3D_Matrix4x4f TE3D_Matrix3x2f_ExpandTo4x4(TE3D_Matrix3x2f matrix)
{
	TE3D_Matrix4x4f result;
	result.m11 = matrix.m11;
	result.m12 = matrix.m12;
	result.m13 = matrix.m13;
	result.m14 = 0;
	result.m21 = matrix.m21;
	result.m22 = matrix.m22;
	result.m23 = matrix.m23;
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = 0;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 0;
	return result;
}


// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
// plane: A normal vector, that defines the plane to project on.
// worldsup: A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
TE3D_Matrix3x2f TE3D_Transformation3x2f_OrthogonalProjection(TE3D_Vector3f plane, TE3D_Vector3f worldsup);

// Creates a matrix that describes a translation.
// shiftX: The shift of the x-component.
// shiftY: The shift of the y-component.
// shiftZ: The shift of the z-component.
TE3D_Matrix3x3f TE3D_Transformation3x3f_Translation(float shiftX, float shiftY, float shiftZ);

// Creates a matrix that describes a scale.
// scaleX: The scale of the x-component.
// scaleY: The scale of the y-component.
// scaleZ: The scale of the z-component.
TE3D_Matrix3x3f TE3D_Transformation3x3f_Scale(float scaleX, float scaleY, float scaleZ);






// Describes a color with red, green and blue components.
struct TE3D_Color
{
	// The red portion of the color.
	char R;
	// The green portion of the color.
	char G;
	// The blue portion of the color.
	char B;
}

// Describes a colorized char.
struct TE3D_ColorChar
{
	// The char.
	char Char;
	// The color of the char.
	TE3D_Color Color;
}

// Describes a surface of colorized chars.
struct TE3D_Surface
{
	// The colorized chars of the surface.
	TE3D_Color Pixels[];
	// The width and height of the surface.
	int Width;
	int Height;
	// The stride of the surface.
	int Stride;
}