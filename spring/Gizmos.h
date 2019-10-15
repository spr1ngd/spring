#pragma once
#include <vector>
#include "vector2.h"
#include "axishelper.h"

using namespace std;

namespace spring
{
	class Transform;
	class Gizmos
	{
	private:
		static vector<AxisHelper*> axisHelpers;
		static unsigned int mode;
	public:
		static void DrawAxis(Vector3 pos);
		static void DrawAxis(Transform* transform,Vector3 size = Vector3::one);
		static void DrawLine(Vector2 start,Vector2 end);
		static void DrawVector(Vector2 vec2);

		static void SetMode(unsigned int mode);
		static unsigned int GetMode();
		static void Render();
	};
}