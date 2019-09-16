#pragma once

namespace spring 
{
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
		Vector4(float x,float y,float z,float w);
	};
}