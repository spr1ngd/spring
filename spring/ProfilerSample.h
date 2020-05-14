#pragma once 
#include "timer.h" 

namespace spring 
{
	class ProfilerSample 
	{
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
			elapsedTime = Timer::GetTickCount();
		}
		void EndSample()
		{
			float f = Timer::GetTickCount() - this->elapsedTime;
			this->elapsedTime = f;
		}
	};
}