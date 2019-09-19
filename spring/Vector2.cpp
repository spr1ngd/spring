#include "vector2.h"

using namespace spring;

Vector2 Vector2::one = Vector2(1.0f,1.0f);
Vector2 Vector2::zero = Vector2(0.0f,0.0f);
Vector2 Vector2::half = Vector2(0.5f,0.5f);
Vector2 Vector2::up = Vector2(0.0f,1.0f);
Vector2 Vector2::down = Vector2(0.0f,-1.0f);
Vector2 Vector2::left = Vector2(-1.0f,0.0f);
Vector2 Vector2::right = Vector2(1.0f,0.0f);

Vector2 Vector2::operator+(const Vector2 vec2) 
{
	return Vector2(this->x + vec2.x, this->y + vec2.y);
}

Vector2 Vector2::operator-(const Vector2 vec2) 
{
	return Vector2(this->x - vec2.x, this->y - vec2.y);
}

Vector2 Vector2::operator*(const float multiplicator) 
{
	return Vector2(this->x * multiplicator, this->y * multiplicator);
}

Vector2 Vector2::operator/(const float dividend) 
{
	return Vector2(this->x / dividend, this->y / dividend);
}