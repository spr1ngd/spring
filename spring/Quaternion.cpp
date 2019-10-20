#include "quaternion.h"
#include "matrix4x4.h"

using namespace spring;

Quaternion Quaternion::indentity = Quaternion(0.0f,0.0f,0.0f,1.0f);

Quaternion::Quaternion(float x, float y, float z, float w) 
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Quaternion::Magnitude() const 
{
	return Mathf::Sqrt(this->w * this->w + this->x * this->x + this->y * this->y + this->z * this->z);
}

void Quaternion::Normalize() 
{
	float magnitude = this->Magnitude();
	this->w /= magnitude;
	this->x /= magnitude;
	this->y /= magnitude;
	this->z /= magnitude;
}

Vector3 Quaternion::EulerAngle() const 
{
	// global to local
	Vector3 vec3;
	float sx = -2.0f * (this->y * this->z - this->w * this->x);
	if (Mathf::Abs(sx) > 0.99999f) 
	{
		vec3.x = 1.570796f * sx;
		vec3.y = Mathf::Atan2(-this->x * this->z + this->w * this->y, 0.5f - this->y * this->y - this->z * this->z);
		vec3.z = 0.0f;
	}
	else 
	{
		vec3.x = Mathf::Asin(sx);
		vec3.y = Mathf::Atan2(this->x * this->z + this->w * this->y, 0.5f - this->x * this->x - this->y * this->y);
		vec3.z = Mathf::Atan2(this->x * this->y + this->w * this->z, 0.5f - this->x * this->x - this->z * this->z);
	}
	return Vector3(
		Mathf::Angle(vec3.x),
		Mathf::Angle(vec3.y),
		Mathf::Angle(vec3.z));
}

Quaternion Quaternion::RotateX(float angle) 
{
	Quaternion quaternion;
	float thetaOver2 = Mathf::Radian(angle * 0.5f);
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.x = Mathf::Sin(thetaOver2);
	return quaternion;
}

Quaternion Quaternion::RotateY(float angle) 
{
	Quaternion quaternion;
	float thetaOver2 = Mathf::Radian(angle * 0.5f);
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.y = Mathf::Sin(thetaOver2);
	return quaternion;
}

Quaternion Quaternion::RotateZ(float angle) 
{
	Quaternion quaternion;
	float thetaOver2 = Mathf::Radian(angle * 0.5f);
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.z = Mathf::Sin(thetaOver2);
	return quaternion;
}

Quaternion Quaternion::Rotate(Vector3 axis, float angle) 
{
	axis = Vector3::Normalize(axis);
	Quaternion quaternion;
	float thetaOver2 = Mathf::Radian(angle * 0.5f);
	float sinThetaOver2 = Mathf::Sin(thetaOver2);
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.x = axis.x * sinThetaOver2;
	quaternion.y = axis.y * sinThetaOver2;
	quaternion.z = axis.z * sinThetaOver2;
	return quaternion;
}

Quaternion Quaternion::Euler(const Vector3& eulerangle) 
{
	return Quaternion::Euler(eulerangle.x, eulerangle.y, eulerangle.z);
}

Quaternion Quaternion::Euler(float x, float y, float z) 
{
	Quaternion quaternion;
	Quaternion RX = Quaternion::RotateX(x);
	Quaternion RY = Quaternion::RotateY(y);
	Quaternion RZ = Quaternion::RotateZ(z);
	quaternion = RZ * RX * RY;
	return quaternion;
}

Quaternion Quaternion::Normalize(const Quaternion& rotation)
{
	Quaternion result;
	float magnitude = rotation.Magnitude();
	result.w = rotation.w / magnitude;
	result.x = rotation.x / magnitude;
	result.y = rotation.y / magnitude;
	result.z = rotation.z / magnitude;
	return result;
}

Quaternion Quaternion::Conjugate(const Quaternion& rotation)
{
	Quaternion result;
	result.x = -rotation.x;
	result.y = -rotation.y;
	result.z = -rotation.z;
	return result;
}

Matrix4x4 Quaternion::ToRotationMatrix(const Quaternion& rotation)
{
	float x = rotation.x;
	float y = rotation.y;
	float z = rotation.z;
	float w = rotation.w;
	// todo : matrix4x4 sequence.
	Matrix4x4 result
	(
		2 * x * y - 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z + 2 * w * x, 0.0f,
		1 - 2 * y * y - 2 * z * z, 2 * x * y + 2 * w * z, 2 * x * z - 2 * w * y, 0.0f,
		2 * x * z + 2 * w * y, 2 * y * z - 2 * w * x, 1 - 2 * x * x - 2 * y * y, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
	return result;
}

Quaternion Quaternion::operator*(const Quaternion& quaternion)
{
	Quaternion result;
	result.w = this->w * quaternion.w - this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z;
	result.x = this->w * quaternion.x + this->x * quaternion.w + this->z * quaternion.y - this->y * quaternion.z;
	result.y = this->w * quaternion.y + this->y * quaternion.w + this->x * quaternion.z - this->z * quaternion.x;
	result.z = this->w * quaternion.z + this->z * quaternion.w + this->y * quaternion.x - this->x * quaternion.y;
	return result;
}

Quaternion Quaternion::operator*=(const Quaternion& quaternion) 
{
	*this = *this * quaternion;
	return *this;
}

Vector3 Quaternion::operator*(const Vector3& vec3) 
{
	Matrix4x4 R = Quaternion::ToRotationMatrix(*this);
	return R * vec3;
}

const char* Quaternion::ToString() 
{
	const char* str = new const char[19];
	// todo 
	return str;
}