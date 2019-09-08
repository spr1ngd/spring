#include "input.h"

using namespace spring;

map<KeyCode, KeyCodeInfo> Input::keyCodeCaches;

KeyCodeInfo* Input::GetKeyCodeInfo(KeyCode keycode) 
{
	auto result = keyCodeCaches.find(keycode);
	if (result == keyCodeCaches.end())
		return nullptr;
	return &result->second;
}

bool Input::GetKey(KeyCode keycode)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	return info->state == KeyCodeState::Down;
}

bool Input::GetKeyDown(KeyCode keycode)
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	bool result = (info->state == KeyCodeState::Down) && !info->down;
	info->down = true;
	return result;
}

bool Input::GetKeyUp(KeyCode keycode) 
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr)
		return false;
	bool result = (info->state == KeyCodeState::Up) && !info->up;
	info->up = true;
	return result;
}

void Input::setKeyCodeState(KeyCode keycode, KeyCodeState keycodeState) 
{
	KeyCodeInfo* info = GetKeyCodeInfo(keycode);
	if (info == nullptr) 
	{
		KeyCodeInfo keycodeInfo(keycode,keycodeState);
		auto item = pair<KeyCode, KeyCodeInfo>(keycode,keycodeInfo);
		keyCodeCaches.insert(item);
	}
	else 
	{
		info->state = keycodeState;
		if (keycodeState == KeyCodeState::Down)
			info->up = false;
		else if (keycodeState == KeyCodeState::Up)
			info->down = false;
	}
}