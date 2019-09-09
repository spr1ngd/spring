#include "Vector3.h"

using namespace spring;

float Vector3::Magnitude(const Vector3 vec3)
{
	return sqrtf(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
}

Vector3 Vector3::Normalize(Vector3 vec3)
{
	float magnitude = Vector3::Magnitude(vec3);
	Vector3 normalize = vec3 / magnitude;
	return normalize;
}

float Vector3::Dot(const Vector3 a,const Vector3 b)
{
	float multiValue = a.x * b.x + a.y * b.y + a.z * b.z;
	float aMagnitude = Vector3::Magnitude(a);
	float bMagnitude = Vector3::Magnitude(b);
	float result = multiValue / (aMagnitude * bMagnitude);
	return result;
}

Vector3 Vector3::Cross(const Vector3 a,const Vector3 b)
{
	return Vector3(a.y * b.z - b.y * a.z, a.z * b.x - b.z * a.x, a.x * b.y - b.x * a.y);
}

Vector3 Vector3::operator+(const Vector3 vec3)
{
	return Vector3(this->x + vec3.x, this->y + vec3.y, this->z + vec3.z);
}

Vector3 Vector3::operator-(const Vector3 vec3)
{
	return Vector3(this->x - vec3.x, this->y - vec3.y, this->z - vec3.z);
}

Vector3 Vector3::operator*(const float multiplicand)
{
	return Vector3(this->x * multiplicand, this->y * multiplicand, this->z * multiplicand);
}

Vector3 Vector3::operator/(const float dividend)
{
	return Vector3(this->x / dividend, this->y / dividend, this->z / dividend);
}