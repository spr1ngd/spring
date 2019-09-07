#pragma once
#include "vector3.h"
#include "vector2.h"
#include "color.h"
#include <vector>

namespace spring 
{
	using namespace std;
	class Vertex
	{
	public:
		Vector3 vertex;
		Vector3 normal;
		Vector2 texcoord;
		Vector3 tangent;
		Vector3 bitangent;
		Color color;
	public:
		Vertex();
	};
}