#pragma once
#include "model.h"

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
		Model CreatePrimitive(Primitive::Type type);
	};
}