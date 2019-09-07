#include "Color.h"

using namespace spring;

Color Color::black = Color(0,0,0,255);
Color Color::white = Color(255,255,255,255);
Color Color::red = Color(255,0,0,255);
Color Color::green = Color(0,255,0,255);
Color Color::blue = Color(0,0,255,255);
Color Color::yellow = Color(255,255,0,255);
Color Color::cyan = Color(0,255,255,255);
Color Color::magenta = Color(255,0,255,255);

Color::Color() 
{
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
} 

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}