#include "graphicprofiler.h"

using namespace spring;

unsigned int GraphicProfiler::drawcall = 0;
unsigned int GraphicProfiler::triangles = 0;
unsigned int GraphicProfiler::vertices = 0;
unsigned int GraphicProfiler::indices = 0;

// profiler sample
std::stack<ProfilerSample*> GraphicProfiler::profilersStack;
std::vector<ProfilerSample*> GraphicProfiler::samples;

void GraphicProfiler::ProfilerReset() 
{
	GraphicProfiler::DrawcallReset();
	GraphicProfiler::TriangleReset();
	GraphicProfiler::VerticesReset();
	GraphicProfiler::IndicesReset();

	GraphicProfiler::ClearSample();
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

// profiler sample
void GraphicProfiler::BeginSample(const char* sampleId) 
{
	ProfilerSample* profiler = nullptr;
	for (auto sample : samples)
	{
		if (std::strcmp(sample->sampleId, sampleId) == 0)
		{
			profiler = sample;
			break;
		}
	}
	if (nullptr == profiler)
	{
		profiler = new ProfilerSample(sampleId);
		samples.push_back(profiler);
	}
	profiler->BeginSample();
	profilersStack.push(profiler);
}
void GraphicProfiler::EndSample() 
{
	ProfilerSample* profiler = profilersStack.top();
	profiler->EndSample();
	profilersStack.pop();
}
void GraphicProfiler::ClearSample() 
{
	for (auto sample : samples) 
		delete sample;
	samples.clear();
	while (!profilersStack.empty())
		profilersStack.pop();
}