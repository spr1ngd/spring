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
				SYSTEMTIME  st = { 0 };
				GetLocalTime(&st);

				float currentFrameTime = st.wMilliseconds;
				perFrameElapsed = currentFrameTime - lastFrameTime;
				int result = (int)(1000.0f / perFrameElapsed);
				if (result > 0)
					fps = result;
				lastFrameTime = currentFrameTime;
			}
		};
	}
}