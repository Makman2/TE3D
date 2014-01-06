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

// Describes a 2x2 matrix.
struct TE3D_Matrix2x2f
{
	float m11, m12, m21, m22;
}

// Describes a 3x3 matrix.
struct TE3D_Matrix3x3f
{
	float m11, m12, m13, m21, m22, m23, m31, m32, m33;
}

// Describes a 4x4 matrix.
struct TE3D_Matrix4x4f
{
	float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
}



// Some vector functions.

// Returns a new 3-dimensional vector with predefined values.
inline struct TE3D_Vector3f TE3D_Vector3f_N(float x, float y, float z)
{
	struct TE3D_Vector3f result;
	result.x = x;
	result.y = y;
	result.z = z;
	return result;
}

// Returns scalar-product of two vectors.
inline double TE3D_Vector3f_mul(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

// Multiplicates a vector with a scalar.
inline struct TE3D_Vector3f TE3D_Vector3f_muls(struct TE3D_Vector3f vector, float scalar)
{
	struct TE3D_Vector3f result;
	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	return result;
}

// Divides a vector with a scalar.
inline struct TE3D_Vector3f TE3D_Vector3f_div(struct TE3D_Vector3f vector, float scalar)
{
	struct TE3D_Vector3f result;
	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	result.z = vector.z / scalar;
	return result;
}

// Add two vectors.
inline struct TE3D_Vector3f TE3D_Vector3f_add(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2)
{
	struct TE3D_Vector3f result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

// Subtract two vectors.
inline struct TE3D_Vector3f TE3D_Vector3f_sub(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2)
{
	struct TE3D_Vector3f result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

// Returns the cross-product of two 3-dimensional vectors.
inline struct TE3D_Vector3f TE3D_Vector3f_cross(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2)
{
	struct TE3D_Vector3f result;
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
inline struct TE3D_Vector3f TE3D_Vector3f_project(struct TE3D_Vector3f vector, struct TE3D_Vector3f projectOn)
{
	return TE3D_Vector3f_muls(projectOn, (TE3D_Vector3f_mul(vector, projectOn) / TE3D_Vector3f_mul(projectOn, projectOn)));
}


// Returns a new 2-dimensional vector with predefined values.
inline struct TE3D_Vector2f TE3D_Vector2f_N(float x, float y)
{
	struct TE3D_Vector2f result;
	result.x = x;
	result.y = y;
	return result;
}

// Returns scalar-product of two vectors.
inline double TE3D_Vector2f_mul(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

// Multiplicates a vector with a scalar.
inline struct TE3D_Vector2f TE3D_Vector2f_muls(struct TE3D_Vector2f vector, float scalar)
{
	struct TE3D_Vector2f result;
	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	return result;
}

// Divides a vector with a scalar.
inline struct TE3D_Vector2f TE3D_Vector2f_div(struct TE3D_Vector2f vector, float scalar)
{
	struct TE3D_Vector2f result;
	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	return result;
}

// Add two vectors.
inline struct TE3D_Vector2f TE3D_Vector2f_add(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2)
{
	struct TE3D_Vector2f result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return result;
}

// Subtract two vectors.
inline struct TE3D_Vector2f TE3D_Vector2f_sub(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2)
{
	struct TE3D_Vector2f result;
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
inline struct TE3D_Vector2f TE3D_Vector2f_project(struct TE3D_Vector2f vector, struct TE3D_Vector2f projectOn)
{
	return TE3D_Vector2f_muls(projectOn, (TE3D_Vector2f_mul(vector, projectOn) / TE3D_Vector2f_mul(projectOn, projectOn)));
}

// Multiplicates a 2x2 matrix with a 2-dimensional vector.
inline struct TE3D_Vector2f TE3D_Matrix2x2f_mul2(struct TE3D_Matrix2x2f matrix, struct TE3D_Vector2f vector)
{
	struct TE3D_Vector2f result;
	result.x = vector.x * matrix.m11 + vector.y * matrix.m12;
	result.y = vector.x * matrix.m21 + vector.y * matrix.m22;
	return result;
}

// Multiplicates a 3x3 matrix with a 3-dimensional vector.
inline struct TE3D_Vector3f TE3D_Matrix3x3f_mul3(struct TE3D_Matrix3x3f matrix, struct TE3D_Vector3f vector)
{
	struct TE3D_Vector3f result;
	result.x = vector.x * matrix.m11 + vector.y * matrix.m12 + vector.z * matrix.m13;
	result.y = vector.x * matrix.m21 + vector.y * matrix.m22 + vector.z * matrix.m23;
	result.z = vector.x * matrix.m31 + vector.y * matrix.m32 + vector.z * matrix.m33;
	return result;
}

// Multiplicates a 4x4 matrix with a 4-dimensional vector.
inline struct TE3D_Vector4f TE3D_Matrix4x4f_mul4(struct TE3D_Matrix4x4f matrix, struct TE3D_Vector4f vector)
{
	struct TE3D_Vector4f result;
	result.x = vector.x * matrix.m11 + vector.y * matrix.m12 + vector.z * matrix.m13 + vector.w * matrix.m14;
	result.y = vector.x * matrix.m21 + vector.y * matrix.m22 + vector.z * matrix.m23 + vector.w * matrix.m24;
	result.z = vector.x * matrix.m31 + vector.y * matrix.m32 + vector.z * matrix.m33 + vector.w * matrix.m34;
	result.w = vector.x * matrix.m41 + vector.y * matrix.m42 + vector.z * matrix.m43 + vector.w * matrix.m44;
	return result;
}

// Multiplicates a 2x2 matrix with a 2x2 matrix.
inline struct TE3D_Matrix2x2f TE3D_Matrix2x2f_mul(struct TE3D_Matrix2x2f matrixA, struct TE3D_Matrix2x2f matrixB)
{
	struct TE3D_Matrix2x2f result;
	result.m11 = matrixA.m11 * matrixB.m11 + matrixA.m12 * matrixB.m21;
	result.m12 = matrixA.m11 * matrixB.m12 + matrixA.m12 * matrixB.m22;
	result.m21 = matrixA.m21 * matrixB.m11 + matrixA.m22 * matrixB.m21;
	result.m22 = matrixA.m21 * matrixB.m12 + matrixA.m22 * matrixB.m22;
	return result;
}

// Multiplicates a 3x3 matrix with a 3x3 matrix.
inline struct TE3D_Matrix3x3f TE3D_Matrix3x3f_mul(struct TE3D_Matrix3x3f matrixA, struct TE3D_Matrix3x3f matrixB)
{
	struct TE3D_Matrix2x2f result;
	result.m11 = matrixA.m11 * matrixB.m11 + matrixA.m12 * matrixB.m21 + matrixA.m13 * matrixB.m31;
	result.m12 = matrixA.m11 * matrixB.m12 + matrixA.m12 * matrixB.m22 + matrixA.m13 * matrixB.m32;
	result.m13 = matrixA.m11 * matrixB.m13 + matrixA.m12 * matrixB.m23 + matrixA.m13 * matrixB.m33;
	result.m21 = matrixA.m21 * matrixB.m11 + matrixA.m22 * matrixB.m21 + matrixA.m23 * matrixB.m31;
	result.m22 = matrixA.m21 * matrixB.m12 + matrixA.m22 * matrixB.m22 + matrixA.m23 * matrixB.m32;
	result.m23 = matrixA.m21 * matrixB.m13 + matrixA.m22 * matrixB.m23 + matrixA.m23 * matrixB.m33;
	result.m31 = matrixA.m31 * matrixB.m11 + matrixA.m32 * matrixB.m21 + matrixA.m33 * matrixB.m31;
	result.m32 = matrixA.m31 * matrixB.m12 + matrixA.m32 * matrixB.m22 + matrixA.m33 * matrixB.m32;
	result.m33 = matrixA.m31 * matrixB.m13 + matrixA.m32 * matrixB.m23 + matrixA.m33 * matrixB.m33;
	return result;
}

// Multiplicates a 3x3 matrix with a 4x4 matrix.
inline struct TE3D_Matrix4x4f TE3D_Matrix4x4f_mul(struct TE3D_Matrix4x4f matrixA, struct TE3D_Matrix4x4f matrixB)
{
	struct TE3D_Matrix2x2f result;
	result.m11 = matrixA.m11 * matrixB.m11 + matrixA.m12 * matrixB.m21 + matrixA.m13 * matrixB.m31 + matrixA.m14 * matrixB.m41;
	result.m12 = matrixA.m11 * matrixB.m12 + matrixA.m12 * matrixB.m22 + matrixA.m13 * matrixB.m32 + matrixA.m14 * matrixB.m42;
	result.m13 = matrixA.m11 * matrixB.m13 + matrixA.m12 * matrixB.m23 + matrixA.m13 * matrixB.m33 + matrixA.m14 * matrixB.m43;
	result.m14 = matrixA.m11 * matrixB.m14 + matrixA.m12 * matrixB.m24 + matrixA.m13 * matrixB.m34 + matrixA.m14 * matrixB.m44;
	result.m21 = matrixA.m21 * matrixB.m11 + matrixA.m22 * matrixB.m21 + matrixA.m23 * matrixB.m31 + matrixA.m24 * matrixB.m41;
	result.m22 = matrixA.m21 * matrixB.m12 + matrixA.m22 * matrixB.m22 + matrixA.m23 * matrixB.m32 + matrixA.m24 * matrixB.m42;
	result.m23 = matrixA.m21 * matrixB.m13 + matrixA.m22 * matrixB.m23 + matrixA.m23 * matrixB.m33 + matrixA.m24 * matrixB.m43;
	result.m24 = matrixA.m21 * matrixB.m14 + matrixA.m22 * matrixB.m24 + matrixA.m23 * matrixB.m34 + matrixA.m24 * matrixB.m44;
	result.m31 = matrixA.m31 * matrixB.m11 + matrixA.m32 * matrixB.m21 + matrixA.m33 * matrixB.m31 + matrixA.m34 * matrixB.m41;
	result.m32 = matrixA.m31 * matrixB.m12 + matrixA.m32 * matrixB.m22 + matrixA.m33 * matrixB.m32 + matrixA.m34 * matrixB.m42;
	result.m33 = matrixA.m31 * matrixB.m13 + matrixA.m32 * matrixB.m23 + matrixA.m33 * matrixB.m33 + matrixA.m34 * matrixB.m43;
	result.m34 = matrixA.m31 * matrixB.m14 + matrixA.m32 * matrixB.m24 + matrixA.m33 * matrixB.m34 + matrixA.m34 * matrixB.m44;
	result.m41 = matrixA.m41 * matrixB.m11 + matrixA.m42 * matrixB.m21 + matrixA.m43 * matrixB.m31 + matrixA.m44 * matrixB.m41;
	result.m42 = matrixA.m41 * matrixB.m12 + matrixA.m42 * matrixB.m22 + matrixA.m43 * matrixB.m32 + matrixA.m44 * matrixB.m42;
	result.m43 = matrixA.m41 * matrixB.m13 + matrixA.m42 * matrixB.m23 + matrixA.m43 * matrixB.m33 + matrixA.m44 * matrixB.m43;
	result.m44 = matrixA.m41 * matrixB.m14 + matrixA.m42 * matrixB.m24 + matrixA.m43 * matrixB.m34 + matrixA.m44 * matrixB.m44;
	return result;
}

// Expands a 3-dimensional vector to a 4-dimensional one.
inline struct TE3D_Vector4f TE3D_Vector3f_ExpandTo4(struct TE3D_Vector3f vector)
{
	struct TE3D_Vector4f result;
	result.x = vector.x;
	result.y = vector.y;
	result.z = vector.z;
	result.w = 1;
	return result;
}

// Expands a 3x3 matrix to a 4x4 matrix.
inline struct TE3D_Matrix4x4f TE3D_Matrix3x3f_ExpandTo4x4(struct TE3D_Matrix3x3f matrix)
{
	struct TE3D_Matrix4x4f result;
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
	result.m44 = 1;
	return result;
}

// Expands a 2x2 matrix to a 4x4 matrix.
inline struct TE3D_Matrix4x4f TE3D_Matrix2x2f_ExpandTo4x4(struct TE3D_Matrix2x2f matrix)
{
	struct TE3D_Matrix4x4f result;
	result.m11 = matrix.m11;
	result.m12 = matrix.m12;
	result.m13 = 0;
	result.m14 = 0;
	result.m21 = matrix.m21;
	result.m22 = matrix.m22;
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

// Returns a new 2x2 matrix with predefined values.
inline struct TE3D_Matrix2x2f TE3D_Matrix2x2f_N(float m11, float m12, float m21, float m22)
{
	struct TE3D_Matrix2x2f result;
	result.m11 = m11;
	result.m12 = m12;
	result.m21 = m21;
	result.m22 = m22;
	return result;
}

// Returns a new 3x3 matrix with predefined values.
inline struct TE3D_Matrix3x3f TE3D_Matrix3x3f_N(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	struct TE3D_Matrix3x3f result;
	result.m11 = m11;
	result.m12 = m12;
	result.m13 = m13;
	result.m21 = m21;
	result.m22 = m22;
	result.m23 = m23;
	result.m31 = m31;
	result.m32 = m32;
	result.m33 = m33;
	return result;
}

// Returns a new 4x4 matrix with predefined values.
inline struct TE3D_Matrix4x4f TE3D_Matrix4x4f_N(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	struct TE3D_Matrix4x4f result;
	result.m11 = m11;
	result.m12 = m12;
	result.m13 = m13;
	result.m14 = m14;
	result.m21 = m21;
	result.m22 = m22;
	result.m23 = m23;
	result.m24 = m24;
	result.m31 = m31;
	result.m32 = m32;
	result.m33 = m33;
	result.m34 = m34;
	result.m41 = m41;
	result.m42 = m42;
	result.m43 = m43;
	result.m44 = m44;
	return result;
}

// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
// plane: A normal vector, that defines the plane to project on.
// worldsup: A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjection(struct TE3D_Vector3f plane, struct TE3D_Vector3f worldsup);
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_OrthogonalProjection(struct TE3D_Vector3f plane, struct TE3D_Vector3f worldsup);

// Creates a matrix that describes a translation.
// shiftX: The shift of the x-component.
// shiftY: The shift of the y-component.
// shiftZ: The shift of the z-component.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Translation(float shiftX, float shiftY, float shiftZ);
// Creates a matrix that describes a translation in 2D.
// shiftX: The shift of the x-component.
// shiftY: The shift of the y-component.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Translation(float shiftX, float shiftY);

// Creates a matrix that describes a scale.
// scaleX: The scale of the x-component.
// scaleY: The scale of the y-component.
// scaleZ: The scale of the z-component.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Scale(float scaleX, float scaleY, float scaleZ);
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Scale(float scaleX, float scaleY, float scaleZ);

// Creates a rotation matrix (for x-axis rotation).
// angle: The angle.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateX(double angle);
// Creates a rotation matrix (for y-axis rotation).
// angle: The angle.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateY(double angle);
// Creates a rotation matrix (for z-axis rotation).
// angle: The angle.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateZ(double angle);
// Creates a rotation matrix for any axis through the origin.
// axis: The rotation axis.
// angle: The angle.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateOrigin(struct TE3D_Vector3f axis, double angle);
// Creates a rotation matrix for any axis.
// axis: The rotation axis.
// offset: The offset of the rotation axis.
// angle: The angle.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Rotate(struct TE3D_Vector3f axis, struct TE3D_Vector3f offset, double angle);
// Creates a rotation matrix (for x-axis rotation).
// angle: The angle.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateX(double angle);
// Creates a rotation matrix (for y-axis rotation).
// angle: The angle.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateY(double angle);
// Creates a rotation matrix (for z-axis rotation).
// angle: The angle.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateZ(double angle);
// Creates a rotation matrix for any axis through the origin.
// axis: The rotation axis.
// angle: The angle.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateOrigin(struct TE3D_Vector3f axis, double angle);
// Creates a rotation matrix in 2D-space for any axis through the origin.
// angle: The angle.
struct TE3D_Matrix2x2f TE3D_Transformation2x2f_RotateOrigin(double angle);
// Creates a rotation matrix in 2D-space for any axis.
// offset: The offset of the rotation axis.
// angle: The angle.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Rotate(struct TE3D_Vector3f offset, double angle);

// Creates the identity matrix.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Identity();
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Identity();
struct TE3D_Matrix2x2f TE3D_Transformation2x2f_Identity();


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



//Describes a colored Pixel
struct TE3D_Pixel{
	int r;
	int g;
	int b;

};

//Describes the DrawBuffer for Drawingfunctions
struct TE3D_DrawBuffer{
	int width;
	int legth;
	TE3D_Pixel **data;
};


struct TE3D_Polygon{
	int count;
	TE3D_Vector3f *data;

};


extern TE3D_Pixel getPixel(TE3D_DrawBuffer *buffer, int x, inty);


//Drawing Functions
//Draws the Object on the DrawBuffer

extern void TE3D_Draw_Line(TE3D_DrawBuffer *buffer, struct TE3D_Vector3f pos1, struct TE3D_Vector3f pos2);
extern void TE3D_Draw_Rectangle(TE3D_DrawBuffer *buffer, struct TE3D_Vector3f pos1, struct TE3D_Vector3f pos2);
extern void TE3D_Draw_Triangle(TE3D_DrawBuffer *buffer, TE3D_Vector3f pos1, TE3D_Vector3f pos2, TE3D_Vector3f pos3);
