#include "input.h"
#include "console.h"

using namespace spring;

map<KeyCode, KeyCodeInfo> Input::keyCodeCaches;
map<MouseID, MouseInfo> Input::mouseCaches;

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
		if (keycodeState == InputState::Down)
			info->up = false;
		else if (keycodeState == InputState::Up)
			info->down = false;
	}
}

bool Input::GetKey(KeyCode keycode)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	return info->state == InputState::Down;
}

bool Input::GetKeyDown(KeyCode keycode)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	bool result = (info->state == InputState::Down) && !info->down;
	if(result)
		info->down = true;
	return result;
}

bool Input::GetKeyUp(KeyCode keycode) 
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	bool result = (info->state == InputState::Up) && !info->up;
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
		if (state == InputState::Down)
			info->up = false;
		if (state == InputState::Up)
			info->down = false;
	}
}

bool Input::GetMouse(MouseID mouseId) 
{
	MouseInfo* info = GetMouseInfo(mouseId);
	if (nullptr == info)
		return false;
	return info->state == InputState::Down;
}

bool Input::GetMouseDown(MouseID mouseId) 
{
	MouseInfo* info = GetMouseInfo(mouseId);
	if (nullptr == info)
		return false;
	bool result = (info->state == InputState::Down) && (!info->down) ;
	if( result )
		info->down = true;
	return result;
}

bool Input::GetMouseUp(MouseID mouseId) 
{
	MouseInfo* info = GetMouseInfo(mouseId);
	if (nullptr == info)
		return false;
	bool result = (info->state == InputState::Up) && (!info->up);
	if( result )
		info->up = true;
	return result;
}

#pragma endregion