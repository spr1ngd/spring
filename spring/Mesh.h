#pragma once
#include "GL/glew.h"
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
	public:
		enum Mode 
		{
			Points,
			Lines,
			LineStrip,
			LineLoop,
			Triangles,
			TriangleStrip,
			TriangleFan,
			Quads,
			QuadStrip,
			Polygon
		};
		enum DrawType 
		{
			StaticDraw,
			DynamicDraw,
			StreamDraw
		};
	private:
		bool initialized = false;

		void GenVAO(function<void()> setting);
		void GenVBO();
		void GenEBO();
		GLenum GetDrawMode(Mode mode)
		{
			switch (mode)
			{
			case spring::Mesh::Points:
				return GL_POINTS;
			case spring::Mesh::Lines:
				return GL_LINES;
			case spring::Mesh::LineStrip:
				return GL_LINE_STRIP;
			case spring::Mesh::LineLoop:
				return GL_LINE_LOOP;
			case spring::Mesh::Triangles:
				return GL_TRIANGLES;
			case spring::Mesh::TriangleStrip:
				return GL_TRIANGLE_STRIP;
			case spring::Mesh::TriangleFan:
				return GL_TRIANGLE_FAN;
			case spring::Mesh::Quads:
				return GL_QUADS;
			case spring::Mesh::QuadStrip:
				return GL_QUAD_STRIP;
			case spring::Mesh::Polygon:
				return GL_POLYGON;
			default:
				return GL_TRIANGLES;
			}
		}
		GLenum GetDrawUsage()
		{
			switch (this->drawType)
			{
			case spring::Mesh::StaticDraw:
				return GL_STATIC_DRAW;
			case spring::Mesh::DynamicDraw:
				return GL_DYNAMIC_DRAW;
			case spring::Mesh::StreamDraw:
				return GL_STREAM_DRAW;
			default:
				return GL_STATIC_DRAW;
			}
		}
	public:
		DrawType drawType = DrawType::StaticDraw;
		Mode mode = Mode::Triangles; 

		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures; 

		unsigned int VAO = 0, VBO = 0, EBO = 0;
		Mesh();
		~Mesh();
		Mesh(vector<Vertex> vertices,vector<unsigned int>indices,vector<Texture> textures);

		void Init(function<void()> setting);
		void Draw(function<void()> render = nullptr );
		void DrawInstanced(unsigned int instancedCount,function<void()> render = nullptr);
	};
}