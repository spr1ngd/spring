#pragma once
#include "mesh.h"

namespace spring 
{
	class Primitive
	{
	public:
		enum Type
		{
			Triangle,
			Cube,
			Sphere,
			Cylinder,
			Plane,
		};

		class Cube 
		{

		};

		class Sphere 
		{

		};

	public:
		Mesh* CreatePrimitive(Primitive::Type type);
	};
}