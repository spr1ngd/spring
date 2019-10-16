#pragma once

namespace spring 
{
	class Quaternion 
	{
	public:
		union
		{
			struct
			{
				float x, y, z,w;
			};
		};

		static Quaternion indentity;
	public:
		Quaternion(float x,float y,float z,float w);

	};
}

