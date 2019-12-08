#pragma once
#include "GLFW/glfw3.h"

namespace spring 
{
	namespace editor
	{
		class GUILayout 
		{
		public:
			static void Initialize(GLFWwindow* window);
			static void PreRender();
			static void Render(GLFWwindow* window);

			static bool Begin(const char*name,bool* open ,int flags = 0);
			static void End();
		};
	}
}