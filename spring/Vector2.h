#pragma once

namespace spring 
{
	class Vector2
	{
	public:
		float x, y;

		static Vector2 zero;
		static Vector2 one;
		static Vector2 half;
		static Vector2 up;
		static Vector2 down;
		static Vector2 left;
		static Vector2 right;
	public:
		Vector2() 
		{
			this->x = 0.0f;
			this->y = 0.0f;
		}
		Vector2(float x, float y) 
		{
			this->x = x;
			this->y = y;
		}
	};
}