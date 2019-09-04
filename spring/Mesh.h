#pragma once
#include "glew.h"
#include <vector>
#include "vector2.h"
#include "vector3.h"
#include <functional>

using namespace std;

namespace spring 
{
	class Mesh
	{
	private:
		void GenVAO( function<void()> setting );
		void GenVBO();
		void GenEBO();
	public:
		vector<Vector3> vertices;
		vector<Vector3> normals;
		vector<Vector2> texcoords;
		vector<unsigned int> indices;
		unsigned int indexCount;
		unsigned int vertexCount;

		GLuint VAO, VBO, EBO;
		Mesh();

		void Init(function<void()> setting);
		void Draw(function<void()> render);
	};
}