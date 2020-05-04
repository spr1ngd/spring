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
			Quad,
			Plane,
			Cube,
			Cylinder,
			Sphere,
			Cone,
			Band,
			Mobiusband
		};

		enum GizmoType 
		{
			Move,
			Rotate,
			Scale
		};

	private:
		// add basic parameters for those mesh generator.
		static Mesh* GenTriangle();
		static Mesh* GenQuad();
		static Mesh* GenPlane();
		static Mesh* GenCube();
		static Mesh* GenSphere();
		static Mesh* GenCylinder();
		static Mesh* GenCone();
		static Mesh* GenBand();
		static Mesh* GenMobiusband();

		static GameObject* CreateTriangle();
		static GameObject* CreateQuad();
		static GameObject* CreatePlane();
		static GameObject* CreateCube();
		static GameObject* CreateCylinder();
		static GameObject* CreateSphere();
		static GameObject* CreateCone();
		static GameObject* CreateBand();
		static GameObject* CreateMobiusband();
		static GameObject* CreateGizmoMove();
		static GameObject* CreateGizmoScale();
		static GameObject* CreateGizmoRotate();

	public:
		static Mesh* GenPrimitive(Primitive::Type type);// enable mesh shared
		static GameObject* CreatePrimitive(Primitive::Type primitiveType);
		static GameObject* CreateGizmo(Primitive::GizmoType gizmoType);
	};
}