#include "cursor.h"

using namespace spring;

GLFWwindow* Cursor::window;
Cursor::CursorDisplayMode Cursor::displayMode = Cursor::CursorDisplayMode::Cursor_Normal;

void Cursor::InitializeCursor(GLFWwindow* window)
{
	Cursor::window = window;
	SetCursotMode(displayMode);
}

void Cursor::Reset() 
{
	SetCursotMode(Cursor::CursorDisplayMode::Cursor_Normal);
}

void Cursor::SetCursotMode(Cursor::CursorDisplayMode mode)
{
	displayMode = mode;
	switch (displayMode)
	{
	case spring::Cursor::Cursor_Normal:
		glfwSetInputMode(Cursor::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	case spring::Cursor::Cursor_Hidden:
		glfwSetInputMode(Cursor::window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case spring::Cursor::Cursor_Disable:
		glfwSetInputMode(Cursor::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	default:
		break;
	}
}