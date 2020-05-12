#include "graphicprofiler.h"

using namespace spring;

unsigned int GraphicProfiler::drawcall = 0;
unsigned int GraphicProfiler::triangles = 0;
unsigned int GraphicProfiler::vertices = 0;
unsigned int GraphicProfiler::indices = 0;

void GraphicProfiler::ProfilerReset() 
{
	GraphicProfiler::DrawcallReset();
	GraphicProfiler::TriangleReset();
	GraphicProfiler::VerticesReset();
	GraphicProfiler::IndicesReset();
}

unsigned int GraphicProfiler::GetDrawcall()
{
	return GraphicProfiler::drawcall;
}
void GraphicProfiler::DrawcallIncrease() 
{
	GraphicProfiler::drawcall++;
}
void GraphicProfiler::DrawcallReset() 
{
	GraphicProfiler::drawcall = 0;
}

unsigned int GraphicProfiler::GetTriangles() 
{
	return GraphicProfiler::triangles;
}
void GraphicProfiler::TriangleIncrease(unsigned int count) 
{
	GraphicProfiler::triangles += count;
}
void GraphicProfiler::TriangleReset() 
{
	GraphicProfiler::triangles = 0;
}

unsigned int GraphicProfiler::GetVertices() 
{
	return GraphicProfiler::vertices;
}
void GraphicProfiler::VerticesIncrease(unsigned int count) 
{
	GraphicProfiler::vertices += count;
}
void GraphicProfiler::VerticesReset() 
{
	GraphicProfiler::vertices = 0;
}

unsigned int GraphicProfiler::GetIndices() 
{
	return GraphicProfiler::indices;
}
void GraphicProfiler::IndicesIncrease(unsigned int count) 
{
	GraphicProfiler::indices += count;
}
void GraphicProfiler::IndicesReset() 
{
	GraphicProfiler::indices = 0;
}