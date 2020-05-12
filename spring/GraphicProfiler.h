#pragma once

namespace spring 
{
	class GraphicProfiler 
	{
	private:
		static unsigned int drawcall;
		static unsigned int vertices;
		static unsigned int indices;
		static unsigned int triangles;

	public:
		static unsigned int GetDrawcall();
		static void DrawcallIncrease();
		static void DrawcallReset();

		static unsigned int GetTriangles();
		static void TriangleIncrease(unsigned int count);
		static void TriangleReset();

		static unsigned int GetVertices();
		static void VerticesIncrease(unsigned int count);
		static void VerticesReset();

		static unsigned int GetIndices();
		static void IndicesIncrease(unsigned int count);
		static void IndicesReset();

		static void ProfilerReset();
	};
}