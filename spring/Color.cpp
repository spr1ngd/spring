#include "color.h"
#include "mathf.h"

using namespace spring;

Color Color::black = Color(0,0,0,255);
Color Color::white = Color(255,255,255,255);
Color Color::red = Color(255,0,0,255);
Color Color::green = Color(0,255,0,255);
Color Color::blue = Color(0,0,255,255);
Color Color::yellow = Color(255,255,0,255);
Color Color::cyan = Color(0,255,255,255);
Color Color::magenta = Color(255,0,255,255);
Color Color::gray = Color(128,128,128,255);

Color::Color() 
{
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
} 

Color::Color( unsigned char color )   
{
	this->r = color;
	this->g = color;
	this->b = color;
	this->a = color;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color Color::operator=(const Colorf color) 
{
	unsigned char r = (unsigned char)(color.r * 255.0f);
	unsigned char g = (unsigned char)(color.g * 255.0f);
	unsigned char b = (unsigned char)(color.b * 255.0f);
	unsigned char a = (unsigned char)(color.a * 255.0f);
	return Color(r,g,b,a);
}

Color Color::operator+(const Color color) 
{
	unsigned char r = Mathf::Clamp(this->r + color.r, 0, 255);
	unsigned char g = Mathf::Clamp(this->g + color.g, 0, 255);
	unsigned char b = Mathf::Clamp(this->b + color.b, 0, 255);
	unsigned char a = Mathf::Clamp(this->a + color.a, 0, 255);
	return Color(r,g,b,a);
}

Color Color::operator-(const Color color) 
{
	unsigned char r = Mathf::Clamp(this->r - color.r, 0, 255);
	unsigned char g = Mathf::Clamp(this->g - color.g, 0, 255);
	unsigned char b = Mathf::Clamp(this->b - color.b, 0, 255);
	unsigned char a = Mathf::Clamp(this->a - color.a, 0, 255);
	return Color(r, g, b, a);
}

Color Color::operator*(const float f) 
{
	unsigned char r = Mathf::Clamp((unsigned char)(this->r * f), 0, 255);
	unsigned char g = Mathf::Clamp((unsigned char)(this->g * f), 0, 255);
	unsigned char b = Mathf::Clamp((unsigned char)(this->b * f), 0, 255);
	unsigned char a = Mathf::Clamp((unsigned char)(this->a * f), 0, 255);
	return Color(r, g, b, a);
}

Color Color::operator/(const float f) 
{
	unsigned char r = Mathf::Clamp((unsigned char)(this->r / f), 0, 255);
	unsigned char g = Mathf::Clamp((unsigned char)(this->g / f), 0, 255);
	unsigned char b = Mathf::Clamp((unsigned char)(this->b / f), 0, 255);
	unsigned char a = Mathf::Clamp((unsigned char)(this->a / f), 0, 255);
	return Color(r, g, b, a);
}