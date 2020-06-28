#include "colorf.h"
#include "mathf.h"

using namespace spring;

Colorf Colorf::red = Colorf(1.0f, 0.0f, 0.0f, 1.0f);
Colorf Colorf::green = Colorf(0.0f, 1.0f, 0.0f, 1.0f);
Colorf Colorf::blue = Colorf(0.0f, 0.0f, 1.0f, 1.0f);
Colorf Colorf::yellow = Colorf(1.0f, 1.0f, 0.0f, 1.0f);
Colorf Colorf::cyan = Colorf(0.0f, 1.0f, 1.0f, 0.0f);
Colorf Colorf::megenta = Colorf(1.0f, 0.0f, 1.0f, 1.0f);
Colorf Colorf::white = Colorf(1.0f, 1.0f, 1.0f, 1.0f);
Colorf Colorf::black = Colorf(0.0f, 0.0f, 0.0f, 1.0f);
Colorf Colorf::gray = Colorf(0.5f, 0.5f, 0.5f, 1.0f);
Colorf Colorf::clear = Colorf(0.0f,0.0f,0.0f,1.0f);

Colorf Colorf::Lerp(Colorf a,Colorf b,const float value) 
{
	float oneMinus = 1.0f - value;
	return a * oneMinus + b * value;
}

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

void Colorf::operator=(const Color color)
{
	this->r = color.r / 255.0f;
	this->g = color.g / 255.0f;
	this->b = color.b / 255.0f;
	this->a = color.a / 255.0f;
}

void Colorf::operator=(const Colorf colorf) 
{
	this->r = colorf.r;
	this->g = colorf.g;
	this->b = colorf.b;
	this->a = colorf.a;
} 

Colorf Colorf::operator+(const Colorf color)
{
	float r = Mathf::Clamp(this->r + color.r, 0.0f, 1.0f);
	float g = Mathf::Clamp(this->g + color.g, 0.0f, 1.0f);
	float b = Mathf::Clamp(this->b + color.b, 0.0f, 1.0f);
	float a = Mathf::Clamp(this->a + color.a, 0.0f, 1.0f);
	return Colorf(r, g, b, a);
}

Colorf Colorf::operator-(const Colorf color)
{
	float r = Mathf::Clamp(this->r - color.r, 0.0f, 1.0f);
	float g = Mathf::Clamp(this->g - color.g, 0.0f, 1.0f);
	float b = Mathf::Clamp(this->b - color.b, 0.0f, 1.0f);
	float a = Mathf::Clamp(this->a - color.a, 0.0f, 1.0f);
	return Colorf(r, g, b, a);
}

Colorf Colorf::operator*(const float f)
{
	float r = Mathf::Clamp(this->r * f, 0.0f, 1.0f);
	float g = Mathf::Clamp(this->g * f, 0.0f, 1.0f);
	float b = Mathf::Clamp(this->b * f, 0.0f, 1.0f);
	float a = Mathf::Clamp(this->a * f, 0.0f, 1.0f);
	return Colorf(r, g, b, a);
}

Colorf Colorf::operator/(const float f)
{
	float r = Mathf::Clamp(this->r / f, 0.0f, 1.0f);
	float g = Mathf::Clamp(this->g / f, 0.0f, 1.0f);
	float b = Mathf::Clamp(this->b / f, 0.0f, 1.0f);
	float a = Mathf::Clamp(this->a / f, 0.0f, 1.0f);
	return Colorf(r, g, b, a);
}