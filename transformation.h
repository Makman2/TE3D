#pragma once

#include <math.h>
#include <stdlib.h>
#include <string.h>
#ifndef WIN32
		#include <stdbool.h>
#endif



// Describes a 4-dimensional vector.
struct TE3D_Vector4f
{
	float x, y, z, w;
};

// Describes a 3-dimensional Vector
struct TE3D_Vector3f{
	float x;
	float y;
	float z;
};

// Describes a 2-dimensional vector.
struct TE3D_Vector2f
{
	float x, y;
};

// Describes a 2x2 matrix.
struct TE3D_Matrix2x2f
{
	float m11, m12, m21, m22;
};

// Describes a 3x3 matrix.
struct TE3D_Matrix3x3f
{
	float m11, m12, m13, m21, m22, m23, m31, m32, m33;
};

// Describes a 4x4 matrix.
struct TE3D_Matrix4x4f
{
	float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
};


// Some vector functions.

// Returns a new 4-dimensional vector with predefined values.
struct TE3D_Vector4f TE3D_Vector4f_N(float x, float y, float z, float w);
// Returns the scalar-product of two vectors.
float TE3D_Vector4f_mul(struct TE3D_Vector4f v1, struct TE3D_Vector4f v2);
// Multiplicates a vector with a scalar.
struct TE3D_Vector4f TE3D_Vector4f_muls(struct TE3D_Vector4f vector, float scalar);
// Divides a vector with a scalar.
struct TE3D_Vector4f TE3D_Vector4f_div(struct TE3D_Vector4f vector, float scalar);
// Add two vectors.
struct TE3D_Vector4f TE3D_Vector4f_add(struct TE3D_Vector4f v1, struct TE3D_Vector4f v2);
// Subtract two vectors.
struct TE3D_Vector4f TE3D_Vector4f_sub(struct TE3D_Vector4f v1, struct TE3D_Vector4f v2);
// Normalizes the given vector.
void TE3D_Vector4f_normalize(struct TE3D_Vector4f* vector);
// Returns the projection of a vector on another vector.
struct TE3D_Vector4f TE3D_Vector4f_project(struct TE3D_Vector4f vector, struct TE3D_Vector4f projectOn);

// Returns a new 3-dimensional vector with predefined values.
struct TE3D_Vector3f TE3D_Vector3f_N(float x, float y, float z);
// Returns scalar-product of two vectors.
float TE3D_Vector3f_mul(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2);
// Multiplicates a vector with a scalar.
struct TE3D_Vector3f TE3D_Vector3f_muls(struct TE3D_Vector3f vector, float scalar);
// Divides a vector with a scalar.
struct TE3D_Vector3f TE3D_Vector3f_div(struct TE3D_Vector3f vector, float scalar);
// Add two vectors.
struct TE3D_Vector3f TE3D_Vector3f_add(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2);
// Subtract two vectors.
struct TE3D_Vector3f TE3D_Vector3f_sub(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2);
// Returns the cross-product of two 3-dimensional vectors.
struct TE3D_Vector3f TE3D_Vector3f_cross(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2);
// Normalizes the given vector.
void TE3D_Vector3f_normalize(struct TE3D_Vector3f *vector);
// Returns the projection of a vector on another vector.
struct TE3D_Vector3f TE3D_Vector3f_project(struct TE3D_Vector3f vector, struct TE3D_Vector3f projectOn);

// Returns a new 2-dimensional vector with predefined values.
struct TE3D_Vector2f TE3D_Vector2f_N(float x, float y);
// Returns scalar-product of two vectors.
float TE3D_Vector2f_mul(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2);
// Multiplicates a vector with a scalar.
struct TE3D_Vector2f TE3D_Vector2f_muls(struct TE3D_Vector2f vector, float scalar);
// Divides a vector with a scalar.
struct TE3D_Vector2f TE3D_Vector2f_div(struct TE3D_Vector2f vector, float scalar);
// Add two vectors.
struct TE3D_Vector2f TE3D_Vector2f_add(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2);
// Subtract two vectors.
struct TE3D_Vector2f TE3D_Vector2f_sub(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2);
// Normalizes the given vector.
void TE3D_Vector2f_normalize(struct TE3D_Vector2f* vector);
// Returns the projection of a vector on another vector.
struct TE3D_Vector2f TE3D_Vector2f_project(struct TE3D_Vector2f vector, struct TE3D_Vector2f projectOn);

// Multiplicates a 2x2 matrix with a 2-dimensional vector.
struct TE3D_Vector2f TE3D_Matrix2x2f_mul2(struct TE3D_Matrix2x2f matrix, struct TE3D_Vector2f vector);
// Multiplicates a 3x3 matrix with a 3-dimensional vector.
struct TE3D_Vector3f TE3D_Matrix3x3f_mul3(struct TE3D_Matrix3x3f matrix, struct TE3D_Vector3f vector);
// Multiplicates a 4x4 matrix with a 4-dimensional vector.
struct TE3D_Vector4f TE3D_Matrix4x4f_mul4(struct TE3D_Matrix4x4f matrix, struct TE3D_Vector4f vector);
// Multiplicates a 2x2 matrix with a 2x2 matrix.
struct TE3D_Matrix2x2f TE3D_Matrix2x2f_mul(struct TE3D_Matrix2x2f matrixA, struct TE3D_Matrix2x2f matrixB);
// Multiplicates a 3x3 matrix with a 3x3 matrix.
struct TE3D_Matrix3x3f TE3D_Matrix3x3f_mul(struct TE3D_Matrix3x3f matrixA, struct TE3D_Matrix3x3f matrixB);
// Multiplicates a 3x3 matrix with a 4x4 matrix.
struct TE3D_Matrix4x4f TE3D_Matrix4x4f_mul(struct TE3D_Matrix4x4f matrixA, struct TE3D_Matrix4x4f matrixB);

// Expands a 2-dimensional vector to a 4-dimensional one.
struct TE3D_Vector4f TE3D_Vector2f_ExpandTo4(struct TE3D_Vector2f vector);
// Expands a 3-dimensional vector to a 4-dimensional one.
struct TE3D_Vector4f TE3D_Vector3f_ExpandTo4(struct TE3D_Vector3f vector);

// Expands a 2x2 matrix to a 4x4 matrix.
struct TE3D_Matrix4x4f TE3D_Matrix2x2f_ExpandTo4x4(struct TE3D_Matrix2x2f matrix);
// Expands a 3x3 matrix to a 4x4 matrix.
struct TE3D_Matrix4x4f TE3D_Matrix3x3f_ExpandTo4x4(struct TE3D_Matrix3x3f matrix);

// Returns a new 2x2 matrix with predefined values.
struct TE3D_Matrix2x2f TE3D_Matrix2x2f_N(float m11, float m12, float m21, float m2);
// Returns a new 3x3 matrix with predefined values.
struct TE3D_Matrix3x3f TE3D_Matrix3x3f_N(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33);
// Returns a new 4x4 matrix with predefined values.
struct TE3D_Matrix4x4f TE3D_Matrix4x4f_N(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44);





// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
// direction: A normal vector, that defines the plane to project on.
// worldsup: A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjection(struct TE3D_Vector3f direction, struct TE3D_Vector3f worldsup);
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_OrthogonalProjection(struct TE3D_Vector3f direction, struct TE3D_Vector3f worldsup);
// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
// direction: A normal vector, that defines the plane to project on.
// offset: The position of the projection plane.
// worldsup: A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjectionWithOffset(struct TE3D_Vector3f direction, struct TE3D_Vector3f offset, struct TE3D_Vector3f worldsup);


// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
// fieldOfView: The view-angle (measured in degrees).
// nearPlane: The distance to the near clipping plane.
// farPlane: The distance to the far clipping plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionZ(double fieldOfView, float nearPlane, float farPlane);
// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
// direction: The direction of the projection.
// fieldOfView: The view-angle.
// nearPlane: The distance to the near clipping plane.
// farPlane: The distance to the far clipping plane.
// worldsup: The worlds up of the projection.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjection(struct TE3D_Vector3f direction, double fieldOfView, float nearPlane, float farPlane, struct TE3D_Vector3f worldsup);
// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
// direction: The direction of the projection.
// fieldOfView: The view-angle.
// nearPlane: The distance to the near clipping plane.
// farPlane: The distance to the far clipping plane.
// offset: The position of the projection plane.
// worldsup: The worlds up of the projection.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionWithOffset(struct TE3D_Vector3f direction, double fieldOfView, float nearPlane, float farPlane, struct TE3D_Vector3f offset, struct TE3D_Vector3f worldsup);

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