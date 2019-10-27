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
			Plane,
			Cube,
			Cylinder,
			Sphere,
		};

	private:
		Mesh* GenTriangle();
		Mesh* GenPlane();
		Mesh* GenCube();
		Mesh* GenCylinder();
		Mesh* GenSphere();
	public:
		Mesh* GenPrimitive(Primitive::Type type);
	};
}