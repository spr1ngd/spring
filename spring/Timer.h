#pragma once
#include <windows.h>

namespace spring 
{
	class Timer
	{
	private:
		static float lastFrameTime;
	public:
		static float deltaTime;
		static float totalTime;
		static void Start();
		static void Time() 
		{
			float currentFrameTime = GetTickCount64() * 0.001f;
			float elapsedTime = currentFrameTime - lastFrameTime;
			deltaTime = elapsedTime;
			lastFrameTime = currentFrameTime;
			totalTime += elapsedTime;
		}

		static float GetTickCount() 
		{
			return (float)GetTickCount64();
		}
	};
}