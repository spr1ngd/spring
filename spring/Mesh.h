#pragma once
#include <vector>
#include "vector2.h"
#include "vector3.h"

using namespace std;

namespace spring 
{
	class Mesh
	{
	public:
		vector<Vector3> positions;
		vector<Vector3> normals;
		vector<Vector2> texcoords;
		vector<unsigned int> indices;
	};
}