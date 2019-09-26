#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

using namespace spring;

Vector4::Vector4() 
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vector4::Vector4(float f) 
{
	this->x = f;
	this->y = f;
	this->z = f;
	this->w = f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::operator spring::Vector2() 
{
	return Vector2(this->x,this->y);
}

Vector4::operator spring::Vector3() 
{
	return Vector3(this->x,this->y,this->z);
}