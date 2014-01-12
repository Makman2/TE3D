#include "graphics.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>
#ifndef WIN32
		#include <stdbool.h>
#endif

#define PI 3.1415926535897932384626433832795
#define ABS(x) (x < 0 ? -x : x)

// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionZ(double fieldOfView, float nearPlane, float farPlane)
{
	// The transformation matrix.
	struct TE3D_Matrix4x4f result;
	
	result.m11 = 1.0f / tan(fieldOfView * 0.5f * (float)PI / 180);
	result.m12 = 0;
	result.m13 = 0;
	result.m14 = 0;
	result.m21 = 0;
	result.m22 = 1.0f / tan(fieldOfView * 0.5f * (float)PI / 180);
	result.m23 = 0;
	result.m24 = 0;
	result.m31 = 0;
	result.m32 = 0;
	result.m33 = farPlane / (farPlane - nearPlane);
	result.m34 = -1;
	result.m41 = 0;
	result.m42 = 0;
	result.m43 = farPlane * nearPlane / (farPlane - nearPlane);
	result.m44 = 0;
	
	return result;
}

// Creates a matrix that describes a perspective projection of 3-dimensional vectors onto a 2-dimensional plane.
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjection(struct TE3D_Vector3f direction, double fieldOfView, float nearPlane, float farPlane, struct TE3D_Vector3f worldsup)
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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_PerspectiveProjectionWithOffset(struct TE3D_Vector3f direction, double fieldOfView, float nearPlane, float farPlane, struct TE3D_Vector3f offset, struct TE3D_Vector3f worldsup)
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

// Creates a matrix that describes an orthogonal projection of 3-dimensional vectors onto a 2-dimensional direction.
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
	xvec = TE3D_Vector3f_cross(direction, xvec);

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
	xvec = TE3D_Vector3f_cross(direction, xvec);

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
	xvec = TE3D_Vector3f_cross(direction, xvec);

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
struct TE3D_Matrix4x4f TE3D_Transformation4x4f_RotateOrigin(struct TE3D_Vector3f axis, double angle)
{
	TE3D_Vector3f_normalize(&axis);

	struct TE3D_Matrix4x4f result;
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
	struct TE3D_Surface* addr = (struct TE3D_Surface*)malloc(sizeof(struct TE3D_Surface) + sizeof(struct TE3D_ColorChar) * width * height);
	memset(addr + 1, 0, sizeof(struct TE3D_ColorChar) * width * height);
	
	// Initialize surface.
	TE3D_Surface* surface = addr;
	surface->Width = width;
	surface->Height = height;
	surface->Stride = sizeof(struct TE3D_ColorChar) * width;
	// Points to the area after the structure.
	surface->Pixels = (struct TE3D_ColorChar*)addr + 1;
	
	return surface;	
}

// Releases a char surface.
// surface: The surface to release.
void TE3D_ReleaseSurface(struct TE3D_Surface* surface)
{
	free(surface);
	
	// Reset struct values.
	surface->Width = 0;
	surface->Height = 0;
	surface->Stride = 0;
	surface->Pixels = NULL;
}