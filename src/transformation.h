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

#include <math.h>
#include <stdlib.h>
#include <string.h>
#ifndef WIN32
		#include <stdbool.h>
#endif

/* TODO define an own type to get independent from float and be able to switch
 * to double fast if needed
 */

// FIXME isnt it better to use arrays for this?
// TODO use typedef with the structs. This is ugly.

/// Describes a 4-dimensional vector.
typedef struct
{
	float x, y, z, w;
} TE3D_Vector4f;

//( Describes a 3-dimensional Vector
typedef struct
{
	float x;
	float y;
	float z;
} TE3D_Vector3f;

/// Describes a 2-dimensional vector.
typedef struct
{
	float x, y;
} TE3D_Vector2f;

/// Describes a 2x2 matrix.
typedef struct
{
	float m11, m12, m21, m22;
} TE3D_Matrix2x2f;

/// Describes a 3x3 matrix.
typedef struct
{
	float m11, m12, m13, m21, m22, m23, m31, m32, m33;
} TE3D_Matrix3x3f;

/// Describes a 4x4 matrix.
typedef struct
{
	float m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44;
} TE3D_Matrix4x4f;


// Some vector functions.

/// Returns a new 4-dimensional vector with predefined values.
TE3D_Vector4f TE3D_Vector4f_N(float x, float y, float z, float w);
/// Returns the scalar-product of two vectors.
float TE3D_Vector4f_mul(TE3D_Vector4f v1, TE3D_Vector4f v2);
/// Multiplicates a vector with a scalar.
TE3D_Vector4f TE3D_Vector4f_muls(TE3D_Vector4f vector, float scalar);
/// Divides a vector with a scalar.
TE3D_Vector4f TE3D_Vector4f_div(TE3D_Vector4f vector, float scalar);
/// Add two vectors.
TE3D_Vector4f TE3D_Vector4f_add(TE3D_Vector4f v1, TE3D_Vector4f v2);
/// Subtract two vectors.
TE3D_Vector4f TE3D_Vector4f_sub(TE3D_Vector4f v1, TE3D_Vector4f v2);
/// Normalizes the given vector.
void TE3D_Vector4f_normalize(TE3D_Vector4f* vector);
/// Returns the projection of a vector on another vector.
TE3D_Vector4f TE3D_Vector4f_project(TE3D_Vector4f vector, TE3D_Vector4f projectOn);

/// Returns a new 3-dimensional vector with predefined values.
TE3D_Vector3f TE3D_Vector3f_N(float x, float y, float z);
/// Returns scalar-product of two vectors.
float TE3D_Vector3f_mul(TE3D_Vector3f v1, TE3D_Vector3f v2);
/// Multiplicates a vector with a scalar.
TE3D_Vector3f TE3D_Vector3f_muls(TE3D_Vector3f vector, float scalar);
/// Divides a vector with a scalar.
TE3D_Vector3f TE3D_Vector3f_div(TE3D_Vector3f vector, float scalar);
/// Add two vectors.
TE3D_Vector3f TE3D_Vector3f_add(TE3D_Vector3f v1, TE3D_Vector3f v2);
/// Subtract two vectors.
TE3D_Vector3f TE3D_Vector3f_sub(TE3D_Vector3f v1, TE3D_Vector3f v2);
/// Returns the cross-product of two 3-dimensional vectors.
TE3D_Vector3f TE3D_Vector3f_cross(TE3D_Vector3f v1, TE3D_Vector3f v2);
/// Normalizes the given vector.
void TE3D_Vector3f_normalize(TE3D_Vector3f *vector);
/// Returns the projection of a vector on another vector.
TE3D_Vector3f TE3D_Vector3f_project(TE3D_Vector3f vector, TE3D_Vector3f projectOn);

/// Returns a new 2-dimensional vector with predefined values.
TE3D_Vector2f TE3D_Vector2f_N(float x, float y);
/// Returns scalar-product of two vectors.
float TE3D_Vector2f_mul(TE3D_Vector2f v1, TE3D_Vector2f v2);
/// Multiplicates a vector with a scalar.
TE3D_Vector2f TE3D_Vector2f_muls(TE3D_Vector2f vector, float scalar);
/// Divides a vector with a scalar.
TE3D_Vector2f TE3D_Vector2f_div(TE3D_Vector2f vector, float scalar);
/// Add two vectors.
TE3D_Vector2f TE3D_Vector2f_add(TE3D_Vector2f v1, TE3D_Vector2f v2);
/// Subtract two vectors.
TE3D_Vector2f TE3D_Vector2f_sub(TE3D_Vector2f v1, TE3D_Vector2f v2);
/// Normalizes the given vector.
void TE3D_Vector2f_normalize(TE3D_Vector2f* vector);
/// Returns the projection of a vector on another vector.
TE3D_Vector2f TE3D_Vector2f_project(TE3D_Vector2f vector, TE3D_Vector2f projectOn);

/// Multiplicates a 2x2 matrix with a 2-dimensional vector.
TE3D_Vector2f TE3D_Matrix2x2f_mul2(TE3D_Matrix2x2f matrix, TE3D_Vector2f vector);
/// Multiplicates a 3x3 matrix with a 3-dimensional vector.
TE3D_Vector3f TE3D_Matrix3x3f_mul3(TE3D_Matrix3x3f matrix, TE3D_Vector3f vector);
/// Multiplicates a 4x4 matrix with a 4-dimensional vector.
TE3D_Vector4f TE3D_Matrix4x4f_mul4(TE3D_Matrix4x4f matrix, TE3D_Vector4f vector);
/// Multiplicates a 2x2 matrix with a 2x2 matrix.
TE3D_Matrix2x2f TE3D_Matrix2x2f_mul(TE3D_Matrix2x2f matrixA, TE3D_Matrix2x2f matrixB);
/// Multiplicates a 3x3 matrix with a 3x3 matrix.
TE3D_Matrix3x3f TE3D_Matrix3x3f_mul(TE3D_Matrix3x3f matrixA, TE3D_Matrix3x3f matrixB);
/// Multiplicates a 3x3 matrix with a 4x4 matrix.
TE3D_Matrix4x4f TE3D_Matrix4x4f_mul(TE3D_Matrix4x4f matrixA, TE3D_Matrix4x4f matrixB);

/// Expands a 2-dimensional vector to a 4-dimensional one.
TE3D_Vector4f TE3D_Vector2f_ExpandTo4(TE3D_Vector2f vector);
/// Expands a 3-dimensional vector to a 4-dimensional one.
TE3D_Vector4f TE3D_Vector3f_ExpandTo4(TE3D_Vector3f vector);

/// Expands a 2x2 matrix to a 4x4 matrix.
TE3D_Matrix4x4f TE3D_Matrix2x2f_ExpandTo4x4(TE3D_Matrix2x2f matrix);
/// Expands a 3x3 matrix to a 4x4 matrix.
TE3D_Matrix4x4f TE3D_Matrix3x3f_ExpandTo4x4(TE3D_Matrix3x3f matrix);

/// Returns a new 2x2 matrix with predefined values.
TE3D_Matrix2x2f TE3D_Matrix2x2f_N(float m11, float m12, float m21, float m2);
/// Returns a new 3x3 matrix with predefined values.
TE3D_Matrix3x3f TE3D_Matrix3x3f_N(float m11, float m12, float m13, float m21,
								  float m22, float m23, float m31, float m32, float m33);
/// Returns a new 4x4 matrix with predefined values.
TE3D_Matrix4x4f TE3D_Matrix4x4f_N(float m11, float m12, float m13, float m14,
								  float m21, float m22, float m23, float m24,
								  float m31, float m32, float m33, float m34,
								  float m41, float m42, float m43, float m44);





/// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
/// @param[in] direction A normal vector, that defines the plane to project on.
/// @param[in] worldsup A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjection(TE3D_Vector3f direction, TE3D_Vector3f worldsup);
TE3D_Matrix3x3f TE3D_Transformation3x3f_OrthogonalProjection(TE3D_Vector3f direction, TE3D_Vector3f worldsup);
/// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
/// @param[in] direction A normal vector, that defines the plane to project on.
/// @param[in] offset The position of the projection plane.
/// @param[in] worldsup A vector that describes the orientation/rotation of the plane (Like the variable says, where the world's top is).
TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjectionWithOffset(TE3D_Vector3f direction, TE3D_Vector3f offset, TE3D_Vector3f worldsup);


/// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
/// @param[in] fieldOfView The view-angle (measured in radians).
/// @param[in]ratio The aspect ratio (width / height).
/// @param[in] nearPlane The distance to the near clipping plane.
/// @param[in] farPlane The distance to the far clipping plane.
TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionZ(double fieldOfView, float ratio, float nearPlane, float farPlane);
// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
// fieldOfView: The view-angle.
// ratio: The aspect ratio (width / height).
// nearPlane: The distance to the near clipping plane.
// farPlane: The distance to the far clipping plane.
// direction: The direction of the projection.
// worldsup: The worlds up of the projection.
TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjection(double fieldOfView, float ratio, float nearPlane, float farPlane, TE3D_Vector3f direction, TE3D_Vector3f worldsup);
/// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
/// @param[in] fieldOfView The view-angle.
/// @param[in] ratio The aspect ratio (width / height).
/// @param[in] nearPlane The distance to the near clipping plane.
/// @param[in] farPlane The distance to the far clipping plane.
/// @param[in] direction The direction of the projection.
/// @param[in] worldsup The worlds up of the projection.
/// @param[in] offset The position of the projection plane.
TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionWithOffset(double fieldOfView, float ratio, float nearPlane, float farPlane, TE3D_Vector3f direction, TE3D_Vector3f worldsup, TE3D_Vector3f offset);

/// Creates a matrix that describes a translation.
/// @param[in] shiftX The shift of the x-component.
/// @param[in] shiftY The shift of the y-component.
/// @param[in] shiftZ The shift of the z-component.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Translation(float shiftX, float shiftY, float shiftZ);
/// Creates a matrix that describes a translation in 2D.
/// @param[in] shiftX The shift of the x-component.
/// @param[in] shiftY The shift of the y-component.
TE3D_Matrix3x3f TE3D_Transformation3x3f_Translation(float shiftX, float shiftY);

/// Creates a matrix that describes a scale.
/// @param[in] scaleX The scale of the x-component.
/// @param[in] scaleY The scale of the y-component.
/// @param[in] scaleZ The scale of the z-component.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Scale(float scaleX, float scaleY, float scaleZ);
TE3D_Matrix3x3f TE3D_Transformation3x3f_Scale(float scaleX, float scaleY, float scaleZ);

/// Creates a rotation matrix (for x-axis rotation).
/// @param[in] angle The angle.
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateX(double angle);
/// Creates a rotation matrix (for y-axis rotation).
/// @param[in] angle The angle.
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateY(double angle);
/// Creates a rotation matrix (for z-axis rotation).
/// @param[in] angle: The angle.
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateZ(double angle);
/// Creates a rotation matrix for any axis through the origin.
/// @param[in] axis: The rotation axis.
/// @param[in] angle: The angle.
TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateOrigin(TE3D_Vector3f axis, double angle);
/// Creates a rotation matrix for any axis.
/// @param[in] axis: The rotation axis.
/// @param[in] offset: The offset of the rotation axis.
/// @param[in] angle: The angle.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Rotate(TE3D_Vector3f axis, TE3D_Vector3f offset, double angle);
/// Creates a rotation matrix (for x-axis rotation).
/// @param[in] angle: The angle.
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateX(double angle);
/// Creates a rotation matrix (for y-axis rotation).
/// @param[in] angle: The angle.
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateY(double angle);
/// Creates a rotation matrix (for z-axis rotation).
/// @param[in] angle: The angle.
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateZ(double angle);
/// Creates a rotation matrix for any axis through the origin.
/// @param[in] axis: The rotation axis.
/// @param[in] angle: The angle.
TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateOrigin(TE3D_Vector3f axis, double angle);
/// Creates a rotation matrix in 2D-space for any axis through the origin.
/// @param[in] angle: The angle.
TE3D_Matrix2x2f TE3D_Transformation2x2f_RotateOrigin(double angle);
/// Creates a rotation matrix in 2D-space for any axis.
/// @param[in] offset: The offset of the rotation axis.
/// @param[in] angle: The angle.
TE3D_Matrix3x3f TE3D_Transformation3x3f_Rotate(TE3D_Vector3f offset, double angle);

/// Creates the identity matrix.
TE3D_Matrix4x4f TE3D_Transformation4x4f_Identity();
TE3D_Matrix3x3f TE3D_Transformation3x3f_Identity();
TE3D_Matrix2x2f TE3D_Transformation2x2f_Identity();
