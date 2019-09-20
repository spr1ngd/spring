#include "Vector3.h"

using namespace spring; 

const Vector3 Vector3::one = Vector3(1.0f);
const Vector3 Vector3::zero = Vector3(0.0f);
const Vector3 Vector3::up = Vector3(0.0f,1.0f,0.0f);
const Vector3 Vector3::down = Vector3(0.0f,-1.0f,0.0f);
const Vector3 Vector3::left = Vector3(-1.0f,0.0f,0.0f);
const Vector3 Vector3::right = Vector3(1.0f,0.0f,0.0f);
const Vector3 Vector3::forward = Vector3(0.0f,-1.0f,0.0f);
const Vector3 Vector3::back = Vector3(0.0f,1.0f,0.0f);

float Vector3::Magnitude(const Vector3 vec3)
{
	return sqrtf(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
}

Vector3 Vector3::Normalize(Vector3& vec3)
{
	if (vec3 == Vector3::zero)
		return Vector3::zero;
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

Vector3 Vector3::Lerp(const Vector3 a, const Vector3 b,const float value)
{
	float oneMinus = 1 - value;
	return Vector3(a.x * value + b.x * oneMinus,
		a.y * value + b.y * oneMinus,
		a.z * value + b.z * oneMinus);
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

void Vector3::operator+=(const Vector3& vec3)
{
	this->x += vec3.x;
	this->y += vec3.y;
	this->z += vec3.z;
}

void Vector3::operator-=(const Vector3& vec3)
{
	this->x -= vec3.x;
	this->y -= vec3.y;
	this->z -= vec3.z;
}

void Vector3::operator*=(const float multiplicand)
{
	this->x *= multiplicand;
	this->y *= multiplicand;
	this->z *= multiplicand;
}

void Vector3::operator/=( const float dividend )
{
	this->x /= dividend;
	this->y /= dividend;
	this->z /= dividend;
}

void Vector3::operator=( const Vector3& vec3 ) 
{
	this->x = vec3.x;
	this->y = vec3.y;
	this->z = vec3.z;
}

bool Vector3::operator==( const Vector3& vec3 )   
{
	return (this->x == vec3.x) && (this->y == vec3.y) && (this->z == vec3.z);
}