#pragma once
#include <vector>
#include "vector2.h"
#include "axishelper.h"
#include "space.h"

using namespace std;

namespace spring
{
	class Transform;
	class Gizmos
	{
	private:
		Material* material;
		Mesh* mesh;
		MeshRenderer* meshrenderer;

		static vector<Gizmos*> gizmos;
		static vector<AxisHelper*> axisHelpers;
		static CoordinateSpace space;
	public:
		static Colorf color;
		static void DrawAxis(Vector3 pos, Vector3 size = Vector3::one);
		static void DrawAxis(Transform* transform, Vector3 size = Vector3::one);

		static void DrawLine(Vector3 start, Vector3 end);
		static void DrawCircle(Vector3 pos,Vector3 up,float radius,unsigned int smoothness = 12);
		static void Render();
	};
}