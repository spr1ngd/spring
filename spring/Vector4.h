#pragma once

namespace spring 
{
	class Vector2;
	class Vector3;
	class Vector4 
	{
	public:
		union 
		{
			struct 
			{
				float x, y, z, w;
			};
		};

	public:
		Vector4();
		Vector4(float f);
		Vector4(float x,float y,float z,float w);

		operator Vector2();
		operator Vector3();
	};
}