#pragma once
#include "glew.h"
#include <vector>
#include "vertex.h"
#include "vector2.h"
#include "vector3.h"
#include "texture.h"
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
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures; 

		GLuint VAO, VBO, EBO;
		Mesh();
		Mesh(vector<Vertex> vertices,vector<unsigned int>indices,vector<Texture> textures);

		void Init(function<void()> setting);
		void Draw(function<void()> render);
	};
}