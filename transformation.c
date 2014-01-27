#include "transformation.h"

#define PI 3.1415926535897932384626433832795
#define ABS(x) (x < 0 ? -x : x)

// Returns a new 4-dimensional vector with predefined values.
inline struct TE3D_Vector4f TE3D_Vector4f_N(float x, float y, float z, float w)
{
	struct TE3D_Vector4f result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;
	return result;
}

// Returns the scalar-product of two vectors.
inline float TE3D_Vector4f_mul(struct TE3D_Vector4f v1, struct TE3D_Vector4f v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

// Multiplicates a vector with a scalar.
inline struct TE3D_Vector4f TE3D_Vector4f_muls(struct TE3D_Vector4f vector, float scalar)
{
	struct TE3D_Vector4f result;
	result.x = vector.x * scalar;
	result.y = vector.y * scalar;
	result.z = vector.z * scalar;
	result.w = vector.w * scalar;
	return result;
}

// Divides a vector with a scalar.
inline struct TE3D_Vector4f TE3D_Vector4f_div(struct TE3D_Vector4f vector, float scalar)
{
	struct TE3D_Vector4f result;
	result.x = vector.x / scalar;
	result.y = vector.y / scalar;
	result.z = vector.z / scalar;
	result.w = vector.w / scalar;
	return result;
}

// Add two vectors.
inline struct TE3D_Vector4f TE3D_Vector4f_add(struct TE3D_Vector4f v1, struct TE3D_Vector4f v2)
{
	struct TE3D_Vector4f result;
	result.x = v1.x / v2.x;
	result.y = v1.y / v2.y;
	result.z = v1.z / v2.z;
	result.w = v1.w / v2.w;
	return result;
}

// Subtract two vectors.
inline struct TE3D_Vector4f TE3D_Vector4f_sub(struct TE3D_Vector4f v1, struct TE3D_Vector4f v2)
{
	struct TE3D_Vector4f result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return result;
}

// Normalizes the given vector.
inline void TE3D_Vector4f_normalize(struct TE3D_Vector4f* vector)
{
	float norm = sqrt(TE3D_Vector4f_mul((*vector), (*vector)));
	vector->x /= norm;
	vector->y /= norm;
	vector->z /= norm;
	vector->w /= norm;
}

// Returns the projection of a vector on another vector.
inline struct TE3D_Vector4f TE3D_Vector4f_project(struct TE3D_Vector4f vector, struct TE3D_Vector4f projectOn)
{
	return TE3D_Vector4f_muls(projectOn, (TE3D_Vector4f_mul(vector, projectOn) / TE3D_Vector4f_mul(projectOn, projectOn)));
}


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
inline float TE3D_Vector3f_mul(struct TE3D_Vector3f v1, struct TE3D_Vector3f v2)
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
inline void TE3D_Vector3f_normalize(struct TE3D_Vector3f *vector)
{
	float norm = sqrt(TE3D_Vector3f_mul((*vector), (*vector)));
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
inline float TE3D_Vector2f_mul(struct TE3D_Vector2f v1, struct TE3D_Vector2f v2)
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
inline void TE3D_Vector2f_normalize(struct TE3D_Vector2f* vector)
{
	float norm = sqrt(TE3D_Vector2f_mul((*vector), (*vector)));
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
	struct TE3D_Matrix3x3f result;
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
	struct TE3D_Matrix4x4f result;
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


// Expands a 2-dimensional vector to a 4-dimensional one.
inline struct TE3D_Vector4f TE3D_Vector2f_ExpandTo4(struct TE3D_Vector2f vector)
{
	struct TE3D_Vector4f result;
	result.x = vector.x;
	result.y = vector.y;
	result.z = 0;
	result.w = 1;
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

// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionZ(double fieldOfView, float ratio, float nearPlane, float farPlane)
{
	// The transformation matrix.
	struct TE3D_Matrix4x4f result;
	
	result.m11 = 1.0f / tan(fieldOfView * 0.5f) / ratio;	result.m12 = 0;	result.m13 = 0;	result.m14 = 0;	result.m21 = 0;	result.m22 = 1.0f / tan(fieldOfView * 0.5f);	result.m23 = 0;	result.m24 = 0;	result.m31 = 0;	result.m32 = 0;	result.m33 = farPlane / (farPlane - nearPlane);	result.m34 = nearPlane * farPlane / (nearPlane - farPlane);	result.m41 = 0;	result.m42 = 0;	result.m43 = 1;	result.m44 = 0;
	
	return result;
}

// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjection(double fieldOfView, float ratio, float nearPlane, float farPlane, struct TE3D_Vector3f direction, struct TE3D_Vector3f worldsup)
{
	// The transformation matrix.
	struct TE3D_Matrix4x4f result;
	
	// Translate back the vectors and rotate the camera (Z-axis: worldsup, X-Y-axis: direction).
		
	// Project on x-z and y-z plane to get angles.
	struct TE3D_Vector3f unitX = TE3D_Vector3f_N(1, 0, 0);
	struct TE3D_Vector3f unitY = TE3D_Vector3f_N(0, 1, 0);
	struct TE3D_Vector3f unitZ = TE3D_Vector3f_N(0, 0, 1);
	
	TE3D_Vector3f_normalize(&direction);
	struct TE3D_Vector3f xzproj = TE3D_Vector3f_add(TE3D_Vector3f_muls(unitX, TE3D_Vector3f_mul(direction, unitX)), TE3D_Vector3f_muls(unitZ, TE3D_Vector3f_mul(direction, unitZ)));
	TE3D_Vector3f_normalize(&xzproj);
	double angleY = ABS(acos((double)TE3D_Vector3f_mul(unitZ, xzproj)));
	double angleXZ = ABS(acos((double)TE3D_Vector3f_mul(unitY, direction))); //X-Z is an axis anywhere in the X-Z plane. It's the cross-product of Y and the direction.
	angleXZ = PI / 2 - angleXZ;
	struct TE3D_Vector3f XZaxis = TE3D_Vector3f_cross(unitY, direction);
	
	if (direction.x < 0)
		angleY *= -1;
	if (direction.y > 0)
		angleXZ *= -1;
	
	// Project worldsup on the X-Y plane.
	worldsup.z = 0;
	TE3D_Vector3f_normalize(&worldsup);
	double angleZ = ABS(acos(TE3D_Vector3f_mul(unitY, worldsup)));
	if (worldsup.x < 0)
		angleZ *= -1;
	
	result.m11 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * (cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x  * XZaxis.x) - sin(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) - sin(angleZ) * (cos(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) - sin(angleY) * (-sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m12 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (-sin(angleZ) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.y) + cos(angleZ) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y - sin(angleXZ) * XZaxis.z));
	result.m13 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * (sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) + cos(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) - sin(angleZ) * (sin(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) + cos(angleY) * (-sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m14 = 0;
	result.m21 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (sin(angleZ) * (cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) - sin(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) + cos(angleZ) * (cos(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) - sin(angleY) * ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m22 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.y) + sin(angleZ) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y - sin(angleXZ) * XZaxis.z));
	result.m23 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (sin(angleZ) * (sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) + cos(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) + cos(angleZ) * (sin(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) + cos(angleY) * ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m24 = 0;
	result.m31 = 1 / (farPlane - nearPlane) * (cos(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) - sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane;
	result.m32 = ((sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * farPlane) / (farPlane - nearPlane);
	result.m33 = 1 / (farPlane - nearPlane) * (sin(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) + cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane;
	result.m34 =  - 1;
	result.m41 = 1 / (farPlane - nearPlane) * (cos(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) - sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane * nearPlane;
	result.m42 = ((sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * farPlane * nearPlane) / (farPlane - nearPlane);
	result.m43 = 1 / (farPlane - nearPlane) * (sin(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) + cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane * nearPlane;
	result.m44 = 0;
	
	return result;
}

// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionWithOffset(double fieldOfView, float ratio, float nearPlane, float farPlane, struct TE3D_Vector3f direction, struct TE3D_Vector3f worldsup, struct TE3D_Vector3f offset)
{
	// The transformation matrix.
	struct TE3D_Matrix4x4f result;
	
	// Translate back the vectors and rotate the camera (Z-axis: worldsup, X-Y-axis: direction).
		
	// Project on x-z and y-z plane to get angles.
	struct TE3D_Vector3f unitX = TE3D_Vector3f_N(1, 0, 0);
	struct TE3D_Vector3f unitY = TE3D_Vector3f_N(0, 1, 0);
	struct TE3D_Vector3f unitZ = TE3D_Vector3f_N(0, 0, 1);
	
	TE3D_Vector3f_normalize(&direction);
	struct TE3D_Vector3f xzproj = TE3D_Vector3f_add(TE3D_Vector3f_muls(unitX, TE3D_Vector3f_mul(direction, unitX)), TE3D_Vector3f_muls(unitZ, TE3D_Vector3f_mul(direction, unitZ)));
	TE3D_Vector3f_normalize(&xzproj);
	double angleY = ABS(acos((double)TE3D_Vector3f_mul(unitZ, xzproj)));
	double angleXZ = ABS(acos((double)TE3D_Vector3f_mul(unitY, direction))); //X-Z is an axis anywhere in the X-Z plane. It's the cross-product of Y and the direction.
	angleXZ = PI / 2 - angleXZ;
	struct TE3D_Vector3f XZaxis = TE3D_Vector3f_cross(unitY, direction);
	if (direction.x < 0)
		angleY *= -1;
	if (direction.y > 0)
		angleXZ *= -1;
	
	// Project worldsup on the X-Y plane.
	worldsup.z = 0;
	TE3D_Vector3f_normalize(&worldsup);
	double angleZ = ABS(acos(TE3D_Vector3f_mul(unitY, worldsup)));
	if (worldsup.x < 0)
		angleZ *= -1;
	
	result.m11 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * (cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) - sin(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) - sin(angleZ) * (cos(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) - sin(angleY) * ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m12 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * ( - sin(angleZ) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.y) + cos(angleZ) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y - sin(angleXZ) * XZaxis.z));
	result.m13 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * (sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) + cos(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) - sin(angleZ) * (sin(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) + cos(angleY) * ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m14 = -1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * ( - ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y - sin(angleXZ) * XZaxis.z) * offset.y + (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) * (sin(angleY) * offset.x - cos(angleY) * offset.z) + (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) * ( - cos(angleY) * offset.x - sin(angleY) * offset.z)) - sin(angleZ) * ( - (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.y) * offset.y + ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * (sin(angleY) * offset.x - cos(angleY) * offset.z) + ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) * ( - cos(angleY) * offset.x - sin(angleY) * offset.z)));
	result.m21 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (sin(angleZ) * (cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) - sin(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) + cos(angleZ) * (cos(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) - sin(angleY) * ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m22 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (cos(angleZ) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.y) + sin(angleZ) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y - sin(angleXZ) * XZaxis.z));
	result.m23 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (sin(angleZ) * (sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) + cos(angleY) * (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z)) + cos(angleZ) * (sin(angleY) * ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) + cos(angleY) * ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z)));
	result.m24 = 1 / tan(fieldOfView * 0.5f * (float)PI / 180) * (sin(angleZ) * ( - ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y - sin(angleXZ) * XZaxis.z) * offset.y + (sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) * (sin(angleY) * offset.x - cos(angleY) * offset.z) + (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.x) * ( - cos(angleY) * offset.x - sin(angleY) * offset.z)) + cos(angleZ) * ( - (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.y) * offset.y + ( - sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * (sin(angleY) * offset.x - cos(angleY) * offset.z) + ((1 - cos(angleXZ)) * XZaxis.x * XZaxis.y + sin(angleXZ) * XZaxis.z) * ( - cos(angleY) * offset.x - sin(angleY) * offset.z)));
	result.m31 = 1 / (farPlane - nearPlane) * (cos(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) - sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane;
	result.m32 = ((sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * farPlane) / (farPlane - nearPlane);
	result.m33 = 1 / (farPlane - nearPlane) * (sin(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) + cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane;
	result.m34 = -1 + 1 / (farPlane - nearPlane) * ( - (sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * offset.y + (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z) * (sin(angleY) * offset.x - cos(angleY) * offset.z) + ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) * ( - cos(angleY) * offset.x - sin(angleY) * offset.z)) * farPlane;
	result.m41 = 1 / (farPlane - nearPlane) * (cos(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) - sin(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane * nearPlane;
	result.m42 = ((sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * farPlane * nearPlane) / (farPlane - nearPlane);
	result.m43 = 1 / (farPlane - nearPlane) * (sin(angleY) * ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) + cos(angleY) * (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z)) * farPlane * nearPlane;
	result.m44 = 1 / (farPlane - nearPlane) * ( - (sin(angleXZ) * XZaxis.x + (1 - cos(angleXZ)) * XZaxis.y * XZaxis.z) * offset.y + (cos(angleXZ) + (1 - cos(angleXZ)) * XZaxis.z * XZaxis.z) * (sin(angleY) * offset.x - cos(angleY) * offset.z) + ( - sin(angleXZ) * XZaxis.y + (1 - cos(angleXZ)) * XZaxis.x * XZaxis.z) * ( - cos(angleY) * offset.x - sin(angleY) * offset.z)) * farPlane * nearPlane;
	
	return result;
}

// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjectionWithOffset(struct TE3D_Vector3f direction, struct TE3D_Vector3f offset, struct TE3D_Vector3f worldsup)
{
	// The transformation matrix.
	struct TE3D_Matrix4x4f result;
	// The ortho-normal span-vectors of the direction.
	struct TE3D_Vector3f xvec, yvec;

	// Normalize direction vector.
	TE3D_Vector3f_normalize(&direction);

	// Gram-Schmidting the worldsup-vector to get the first span-vector.
	yvec = TE3D_Vector3f_sub(worldsup, TE3D_Vector3f_project(worldsup, direction));
	xvec = TE3D_Vector3f_cross(yvec, direction);

	TE3D_Vector3f_normalize(&yvec);
	TE3D_Vector3f_normalize(&xvec);

	result.m11 = xvec.x;
	result.m12 = xvec.y;
	result.m13 = xvec.z;
	result.m14 = - offset.x * xvec.x - offset.y * xvec.y - offset.z * xvec.z;
	result.m21 = yvec.x;
	result.m22 = yvec.y;
	result.m23 = yvec.z;
	result.m24 = - offset.x * yvec.x - offset.y * yvec.y - offset.z * yvec.z;
	result.m31 = direction.x;	// Distance to direction.
	result.m32 = direction.y;
	result.m33 = direction.z;
	result.m34 = - direction.x * offset.x - direction.y * offset.y - direction.z * offset.z;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	
	return result;
}

// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_OrthogonalProjection(struct TE3D_Vector3f direction, struct TE3D_Vector3f worldsup)
{
	// The transformation matrix.
	struct TE3D_Matrix4x4f result;
	// The ortho-normal span-vectors of the direction.
	struct TE3D_Vector3f xvec, yvec;

	// Normalize direction vector.
	TE3D_Vector3f_normalize(&direction);

	// Gram-Schmidting the worldsup-vector to get the first span-vector.
	yvec = TE3D_Vector3f_sub(worldsup, TE3D_Vector3f_project(worldsup, direction));
	xvec = TE3D_Vector3f_cross(yvec, direction);

	TE3D_Vector3f_normalize(&yvec);
	TE3D_Vector3f_normalize(&xvec);

	result.m11 = xvec.x;
	result.m12 = xvec.y;
	result.m13 = xvec.z;
	result.m14 = 0;
	result.m21 = yvec.x;
	result.m22 = yvec.y;
	result.m23 = yvec.z;
	result.m24 = 0;
	result.m31 = direction.x;	// Distance to direction.
	result.m32 = direction.y;
	result.m33 = direction.z;
	result.m34 = 0;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = 0;
	result.m44 = 1;
	
	return result;
}
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_OrthogonalProjection(struct TE3D_Vector3f direction, struct TE3D_Vector3f worldsup)
{
	// The transformation matrix.
	struct TE3D_Matrix3x3f result;
	// The ortho-normal span-vectors of the direction.
	struct TE3D_Vector3f xvec, yvec;

	// Normalize direction vector.
	TE3D_Vector3f_normalize(&direction);

	// Gram-Schmidting the worldsup-vector to get the first span-vector.
	yvec = TE3D_Vector3f_sub(worldsup, TE3D_Vector3f_project(worldsup, direction));
	xvec = TE3D_Vector3f_cross(yvec, direction);

	TE3D_Vector3f_normalize(&yvec);
	TE3D_Vector3f_normalize(&xvec);

	result.m11 = xvec.x;
	result.m12 = xvec.y;
	result.m13 = xvec.z;
	result.m21 = yvec.x;
	result.m22 = yvec.y;
	result.m23 = yvec.z;
	result.m31 = direction.x;			// Distance to direction.
	result.m32 = direction.y;
	result.m33 = direction.z;
	
	return result;
}

// Creates a matrix that describes a translation.
// shiftX: The shift of the x-component.
// shiftY: The shift of the y-component.
// shiftZ: The shift of the z-component.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Translation(float shiftX, float shiftY, float shiftZ)
{
	struct TE3D_Matrix4x4f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Translation(float shiftX, float shiftY)
{
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Scale(float scaleX, float scaleY, float scaleZ)
{
	struct TE3D_Matrix4x4f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Scale(float scaleX, float scaleY, float scaleZ)
{
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Identity()
{
	struct TE3D_Matrix4x4f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Identity()
{
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix2x2f TE3D_Transformation2x2f_Identity()
{
	struct TE3D_Matrix2x2f result;
	result.m11 = 1;
	result.m12 = 0;
	result.m21 = 0;
	result.m22 = 1;
	return result;
}

// Creates a rotation matrix for any axis.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_Rotate(struct TE3D_Vector3f axis, struct TE3D_Vector3f offset, double angle)
{
	TE3D_Vector3f_normalize(&axis);
	
	struct TE3D_Matrix4x4f result;
	result.m11 = axis.x * axis.x * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m12 = axis.x * axis.y * (1 - (float)cos(angle)) - axis.z * (float)sin(angle);
	result.m13 = axis.x * axis.z * (1 - (float)cos(angle)) + axis.y * (float)sin(angle);
	result.m14 = offset.x - ((float)cos(angle) + (1 - (float)cos(angle)) * axis.x * axis.x) * offset.x - ((1 - (float)cos(angle)) * axis.x * axis.y - (float)sin(angle) * axis.z) * offset.y - ((float)sin(angle) * axis.y + (1 - (float)cos(angle)) * axis.x * axis.z) * offset.z;
	result.m21 = axis.x * axis.y * (1 - (float)cos(angle)) + axis.z * (float)sin(angle);
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateOrigin(struct TE3D_Vector3f axis, double angle)
{
	TE3D_Vector3f_normalize(&axis);

	struct TE3D_Matrix4x4f result;
	result.m11 = axis.x * axis.x * (1 - (float)cos(angle)) + (float)cos(angle);
	result.m12 = axis.x * axis.y * (1 - (float)cos(angle)) - axis.z * (float)sin(angle);
	result.m13 = axis.x * axis.z * (1 - (float)cos(angle)) + axis.y * (float)sin(angle);
	result.m14 = 0;
	result.m21 = axis.x * axis.y * (1 - (float)cos(angle)) + axis.z * (float)sin(angle);
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateX(double angle)
{
	struct TE3D_Matrix4x4f result;
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateY(double angle)
{
	struct TE3D_Matrix4x4f result;
	result.m11 = (float)cos(angle);
	result.m12 = 0;
	result.m13 = (float)sin(angle);
	result.m14 = 0;
	result.m21 = 0;
	result.m22 = 1;
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateZ(double angle)
{
	struct TE3D_Matrix4x4f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateX(double angle)
{
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateY(double angle)
{
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateZ(double angle)
{
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_RotateOrigin(struct TE3D_Vector3f axis, double angle)
{
	TE3D_Vector3f_normalize(&axis);
	
	struct TE3D_Matrix3x3f result;
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
struct TE3D_Matrix2x2f TE3D_Transformation2x2f_RotateOrigin(double angle)
{	
	struct TE3D_Matrix2x2f result;
	result.m11 = (float)cos(angle);
	result.m12 = -(float)sin(angle);
	result.m21 = (float)sin(angle);
	result.m22 = (float)cos(angle);
	return result;

	
}

// Creates a rotation matrix in 2D-space for any axis.
// offset: The offset of the rotation axis.
// angle: The angle.
struct TE3D_Matrix3x3f TE3D_Transformation3x3f_Rotate(struct TE3D_Vector3f offset, double angle)
{

	struct TE3D_Matrix3x3f result;
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




