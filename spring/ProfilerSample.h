#pragma once 
#include "timer.h" 

namespace spring 
{
	class ProfilerSample 
	{
	private: 
		float beginSampleTick = 0.0f;

	public:
		const char* sampleId = nullptr;
		float elapsedTime = 0.0f;

		ProfilerSample(const char* sampleId) : elapsedTime(0.0f)
		{
			this->sampleId = sampleId;
		}
		~ProfilerSample() = default;

		void BeginSample() 
		{
			beginSampleTick = Timer::GetTickCount();
		}
		void EndSample()
		{
			float f = Timer::GetTickCount() - this->beginSampleTick;
			this->elapsedTime += f;
		}
	};
}