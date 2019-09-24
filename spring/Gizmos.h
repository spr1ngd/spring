#pragma once
#include "vector2.h"
#include "axishelper.h"
#include <vector>

using namespace std;

namespace spring
{
	class Gizmos
	{
		// todo : draw some helper graphic in scene.
		// todo : manage the gizmos in scene.
	private:
		static vector<AxisHelper*> axisHelpers;
	public:
		static void DrawAxis(Vector3 pos);
		static void DrawLine(Vector2 start,Vector2 end);
		static void DrawVector(Vector2 vec2);
	};
}