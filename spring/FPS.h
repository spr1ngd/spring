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
			static float perFrameElapsed;
			static void CalculateFramePerSecond()
			{
				float currentFrameTime = GetTickCount64() * 0.001f;
				perFrameElapsed = currentFrameTime - lastFrameTime;
				int result = (int)(1.0f / perFrameElapsed);
				if (result > 0)
					fps = result;
				lastFrameTime = currentFrameTime;
			}
		};
	}
}