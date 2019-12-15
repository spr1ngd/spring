#pragma once
#include "GLFW/glfw3.h"

namespace spring
{
	class Cursor 
	{
	public:
		enum CursorDisplayMode
		{
			Cursor_Normal,
			Cursor_Hidden,
			Cursor_Disable
		};
	private:
		static GLFWwindow* window;
		static CursorDisplayMode displayMode;

		// cursor object , for customize icon ,size.
	public:
		static void InitializeCursor(GLFWwindow* window);
		static void SetCursotMode(CursorDisplayMode mode);
		static void SetCursorIcon();
		static void Reset();
	};
}