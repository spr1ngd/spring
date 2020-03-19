#include "input.h"
#include "GLFW/glfw3.h"
#include "console.h"
#include "screen.h"

using namespace spring;

map<KeyCode, KeyCodeInfo> Input::keyCodeCaches;
map<MouseID, MouseInfo> Input::mouseCaches;
Vector2 Input::mousePosition;
Vector2 Input::mouseDelta = Vector2::zero;
float Input::mouseWheelDelta;
GLFWwindow* Input::window;

void processKeyInput(KeyCode keyCode, int keyStatus)
{
	if (keyStatus == GLFW_PRESS) Input::setKeyCodeState(keyCode, InputState::STATE_DOWN);
	if (keyStatus == GLFW_RELEASE) Input::setKeyCodeState(keyCode, InputState::STATE_UP);
	if (keyStatus == GLFW_REPEAT) Input::setKeyCodeState(keyCode, InputState::STATE_PRESS);
}

void processMouseInput(MouseID mouseId, int mouseStatus)
{
	if (mouseStatus == GLFW_PRESS) Input::setMouseState(mouseId, InputState::STATE_DOWN);
	if (mouseStatus == GLFW_RELEASE)Input::setMouseState(mouseId, InputState::STATE_UP);
	if (mouseStatus == GLFW_REPEAT)Input::setMouseState(mouseId, InputState::STATE_PRESS);
}

void io_keyboard_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
	switch (key)
	{
	case GLFW_KEY_A:
		processKeyInput(KeyCode::A, action);
		break;
	case GLFW_KEY_B:
		processKeyInput(KeyCode::B, action);
		break;
	case GLFW_KEY_C:
		processKeyInput(KeyCode::C, action);
		break;
	case GLFW_KEY_D:
		processKeyInput(KeyCode::D, action);
		break;
	case GLFW_KEY_E:
		processKeyInput(KeyCode::E, action);
		break;
	case GLFW_KEY_F:
		processKeyInput(KeyCode::F, action);
		break;
	case GLFW_KEY_G:
		processKeyInput(KeyCode::G, action);
		break;
	case GLFW_KEY_H:
		processKeyInput(KeyCode::H, action);
		break;
	case GLFW_KEY_I:
		processKeyInput(KeyCode::I, action);
		break;
	case GLFW_KEY_J:
		processKeyInput(KeyCode::J, action);
		break;
	case GLFW_KEY_K:
		processKeyInput( KeyCode::K, action);
		break;
	case GLFW_KEY_L:
		processKeyInput( KeyCode::L, action);
		break;
	case GLFW_KEY_M:
		processKeyInput( KeyCode::M, action);
		break;
	case GLFW_KEY_N:
		processKeyInput( KeyCode::N, action);
		break;
	case GLFW_KEY_O:
		processKeyInput(KeyCode::O, action);
		break;
	case GLFW_KEY_P:
		processKeyInput( KeyCode::P, action);
		break;
	case GLFW_KEY_Q:
		processKeyInput(KeyCode::Q, action);
		break;
	case GLFW_KEY_R:
		processKeyInput( KeyCode::R, action);
		break;
	case GLFW_KEY_S:
		processKeyInput( KeyCode::S, action);
		break;
	case GLFW_KEY_T:
		processKeyInput( KeyCode::T, action);
		break;
	case GLFW_KEY_U:
		processKeyInput( KeyCode::U, action);
		break;
	case GLFW_KEY_V:
		processKeyInput( KeyCode::V, action);
		break;
	case GLFW_KEY_W:
		processKeyInput( KeyCode::W, action);
		break;
	case GLFW_KEY_X:
		processKeyInput( KeyCode::X, action);
		break;
	case GLFW_KEY_Y:
		processKeyInput( KeyCode::Y, action);
		break;
	case GLFW_KEY_Z:
		processKeyInput( KeyCode::Z, action);
		break;
	default:
		break;
	}
}

void io_mouse_button_callback( GLFWwindow* window,int button,int action ,int mods ) 
{
	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		processMouseInput(MouseID::MOUSE_LEFT, action);
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		processMouseInput(MouseID::MOUSE_RIGHT, action);
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		processMouseInput(MouseID::MOUSE_WHEEL, action);
		break;
	}
}

void io_mouse_wheel_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	Input::setMouseWheel((float)yOffset);
}

void io_cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
	Input::setMousePosition((float)xPos, (float)yPos);
}

void Input::InitializeInput(GLFWwindow* window) 
{
	Input::window = window;
	glfwSetKeyCallback(window, io_keyboard_callback);
	glfwSetMouseButtonCallback(window, io_mouse_button_callback);
	glfwSetScrollCallback(window, io_mouse_wheel_callback);
	glfwSetCursorPosCallback(window, io_cursor_position_callback); // todo : raw mouse motion.
}

#pragma region keyboard events

KeyCodeInfo* Input::GetKeyCodeInfo(KeyCode keycode) 
{
	auto result = keyCodeCaches.find(keycode);
	if (result == keyCodeCaches.end())
		return nullptr;
	return &result->second;
} 

void Input::setKeyCodeState(KeyCode keycode, InputState keycodeState)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
	{
		KeyCodeInfo keycodeInfo(keycode, keycodeState);
		auto item = pair<KeyCode, KeyCodeInfo>(keycode, keycodeInfo);
		keyCodeCaches.insert(item);
	}
	else
	{
		info->state = keycodeState;
		if (keycodeState == InputState::STATE_DOWN)
			info->up = false;
		else if (keycodeState == InputState::STATE_UP)
			info->down = false;
	}
}

bool Input::GetKey(KeyCode keycode)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	return info->state == InputState::STATE_DOWN;
}

bool Input::GetKeyDown(KeyCode keycode)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	bool result = (info->state == InputState::STATE_DOWN) && !info->down;
	if(result)
		info->down = true;
	return result;
}

bool Input::GetKeyUp(KeyCode keycode) 
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	bool result = (info->state == InputState::STATE_UP) && !info->up;
	if(result)
		info->up = true;
	return result;
}  

#pragma endregion

#pragma region mouse events

MouseInfo* Input::GetMouseInfo(MouseID mouseID)
{
	auto result = mouseCaches.find(mouseID);
	if (result == mouseCaches.end())
		return nullptr;
	return &result->second;
}

void Input::setMouseState(MouseID mouseID, InputState state)
{
	MouseInfo* info = GetMouseInfo(mouseID);
	if (nullptr == info) 
	{
		MouseInfo mouseInfo(mouseID, state);
		auto item = std::pair<MouseID, MouseInfo>(mouseID, mouseInfo);
		mouseCaches.insert(item);
	}
	else 
	{
		info->state = state;
		if (state == InputState::STATE_DOWN)
			info->up = false;
		if (state == InputState::STATE_UP)
			info->down = false;
	}
}

void Input::setMouseWheel(float delta) 
{
	MouseInfo* info = GetMouseInfo(MouseID::MOUSE_WHEEL);
	if (nullptr == info)
	{
		MouseInfo mouseInfo(MouseID::MOUSE_WHEEL,InputState::STATE_IDLE);
		mouseInfo.wheelDelta = delta;
		auto item = std::pair<MouseID, MouseInfo>(MouseID::MOUSE_WHEEL,mouseInfo);
		mouseCaches.insert(item);
	}
	else 
	{
		info->wheelDelta = delta;
	}
	Input::mouseWheelDelta = delta;
}

bool Input::GetMouse(MouseID mouseId) 
{
	MouseInfo* info = GetMouseInfo(mouseId);
	if (nullptr == info)
		return false;
	return info->state == InputState::STATE_DOWN;
}

bool Input::GetMouseDown(MouseID mouseId) 
{
	MouseInfo* info = GetMouseInfo(mouseId);
	if (nullptr == info)
		return false;
	bool result = (info->state == InputState::STATE_DOWN) && (!info->down) ;
	if( result )
		info->down = true;
	return result;
}

bool Input::GetMouseUp(MouseID mouseId) 
{
	MouseInfo* info = GetMouseInfo(mouseId);
	if (nullptr == info)
		return false;
	bool result = (info->state == InputState::STATE_UP) && (!info->up);
	if( result )
		info->up = true;
	return result;
}

float Input::GetMouseWheel()
{
	MouseInfo* info = GetMouseInfo(MouseID::MOUSE_WHEEL);
	if (nullptr == info)
		return 0.0f;
	return info->wheelDelta;
}

void Input::setMousePosition(float xPos, float yPos) 
{
	Vector2 newMousePosition = Vector2(xPos, Screen::height - yPos);
	Input::mouseDelta = Vector2(newMousePosition.x - Input::mousePosition.x,Input::mousePosition.y - newMousePosition.y);
	Input::mousePosition = newMousePosition;
}

#pragma endregion