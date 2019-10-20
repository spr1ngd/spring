#include "quaternion.h"

using namespace spring;

Quaternion Quaternion::indentity = Quaternion(0.0f,0.0f,0.0f,1.0f);

Quaternion::Quaternion(float x, float y, float z, float w) 
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

float Quaternion::Angle() const
{
	float halfAngle = Mathf::Angle(Mathf::Acos(this->w));
	return halfAngle * 2;
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

Vector3 Quaternion::AngleAxis() const
{
	float sinine = Mathf::Sqrt(1 - this->w * this->w);
	Vector3 vec3;
	vec3.x = this->x / sinine;
	vec3.y = this->y / sinine;
	vec3.z = this->z / sinine;
	return vec3;
}

Vector3 Quaternion::Eulerangle() const 
{
	Vector3 result;
	return result;
}

Quaternion Quaternion::RotateX(float theta) 
{
	Quaternion quaternion;
	float thetaOver2 = theta * 0.5f;
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.x = Mathf::Sin(thetaOver2);
	return quaternion;
}

Quaternion Quaternion::RotateY(float theta) 
{
	Quaternion quaternion;
	float thetaOver2 = theta * 0.5f;
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.y = Mathf::Sin(thetaOver2);
	return quaternion;
}

Quaternion Quaternion::RotateZ(float theta) 
{
	Quaternion quaternion;
	float thetaOver2 = theta * 0.5f;
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.z = Mathf::Sin(thetaOver2);
	return quaternion;
}

Quaternion Quaternion::Rotate(Vector3 axis, float theta) 
{
	axis = Vector3::Normalize(axis);
	Quaternion quaternion;
	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = Mathf::Sin(thetaOver2);
	quaternion.w = Mathf::Cos(thetaOver2);
	quaternion.x = axis.x * sinThetaOver2;
	quaternion.y = axis.y * sinThetaOver2;
	quaternion.z = axis.z * sinThetaOver2;
	return quaternion;
}

Quaternion Quaternion::Euler(const Vector3& eulerangle) 
{
	// transfer eulerangle to quaternion.
	Quaternion quaternion;
	return quaternion;
}

Quaternion Quaternion::Normalize(const Quaternion& quaternion) 
{
	Quaternion result;
	float magnitude = quaternion.Magnitude();
	result.w = quaternion.w / magnitude;
	result.x = quaternion.x / magnitude;
	result.y = quaternion.y / magnitude;
	result.z = quaternion.z / magnitude;
	return result;
}

Quaternion Quaternion::Conjugate(const Quaternion& quaternion) 
{
	Quaternion result;
	result.x = -quaternion.x;
	result.y = -quaternion.y;
	result.z = -quaternion.z;
	return result;
}

Quaternion Quaternion::operator*(const Quaternion& quaternion)
{
	// Áª½Ó½ÇÎ»ÒÆ
	Quaternion result;
	return result;
}

Quaternion Quaternion::operator*=(const Quaternion& quaternion) 
{
	Quaternion result;
	return result;
}