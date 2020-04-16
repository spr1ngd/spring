#pragma once
#include "mesh.h"
#include "gameobject.h"

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
			Cone,
		};

	private:
		static Mesh* GenTriangle();
		static Mesh* GenPlane();
		static Mesh* GenCube();
		static Mesh* GenCylinder();
		static Mesh* GenSphere();
		static Mesh* GenCone();

		static GameObject* CreateTriangle();
		static GameObject* CreatePlane();
		static GameObject* CreateCube();
		static GameObject* CreateCylinder();
		static GameObject* CreateSphere();
		static GameObject* CreateCone();
	public:
		static Mesh* GenPrimitive(Primitive::Type type);
		static GameObject* CreatePrimitive(Primitive::Type primitiveType);
	};
}