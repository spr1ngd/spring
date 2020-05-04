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
		static vector<Gizmos*> gizmos;
		// static vector<AxisHelper*> axisHelpers;
		static CoordinateSpace space;

		static AxisHelper* axisHelper;
	public:
		static bool enable;
		static Colorf color;

		static void DrawLine(Vector3 start, Vector3 end);
		static void DrawCircle(Vector3 pos,Vector3 up,float radius,unsigned int smoothness = 12);
		static void Render();

		static void DrawAxis(Transform& target);
	};
}