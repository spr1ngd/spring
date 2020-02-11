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
		static Mesh* GenTriangle();
		static Mesh* GenPlane();
		static Mesh* GenCube();
		static Mesh* GenCylinder();
		static Mesh* GenSphere();
	public:
		static Mesh* GenPrimitive(Primitive::Type type);
	};
}