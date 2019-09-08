#pragma once
#include <windows.h>
#include <iostream>

namespace spring 
{
	namespace editor
	{
		class FPS 
		{
		private:
			static float lastFrameTime;
		public:
			static int fps;
			static void CalculateFramePerSecond()
			{
				float currentFrameTime = GetTickCount() * 0.001f;
				float elapsedTime = currentFrameTime - lastFrameTime;
				fps = (int)(1.0f / elapsedTime);
				lastFrameTime = currentFrameTime;
				std::cout << "spring engine FPS " << fps << std::endl;
			}
		};
	}
}