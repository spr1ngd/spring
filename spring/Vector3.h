#pragma once


namespace spring 
{
	class Vector3
	{
	public:
		union 
		{
			struct 
			{
				float x, y, z;
			};
		};
	public:
		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) 
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		float Magnitude();
		void Normalize();
	};
}