#include "colorf.h"

using namespace spring;

Colorf Colorf::red = Colorf(1.0f,0.0f,0.0f,1.0f);

Colorf::Colorf() 
{
	this->r = 1.0f;
	this->g = 1.0f;
	this->b = 1.0f;
	this->a = 1.0f;
}

Colorf::Colorf(float c) 
{
	this->r = c;
	this->g = c;
	this->b = c;
	this->a = c;
}

Colorf::Colorf(float r, float g, float b, float a) 
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}