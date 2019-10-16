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