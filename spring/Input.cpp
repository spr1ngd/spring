#include "input.h"

using namespace spring;

map<KeyCode, KeyCodeInfo> keyCodeCaches;

bool Input::GetKey(KeyCode keycode)
{

}

bool Input::GetKeyDown(KeyCode keycode)
{

}

bool Input::GetKeyUp(KeyCode keycode) 
{

}

void Input::setKeyCodeState(KeyCode keycode, KeyCodeState keycodeState) 
{
	auto result = keyCodeCaches.find(keycode);
	if (result == keyCodeCaches.end()) 
	{
		KeyCodeInfo keycodeInfo(keycode,keycodeState);
		auto item = pair<KeyCode, KeyCodeInfo>(keycode,keycodeInfo);
		keyCodeCaches.insert(item);
	}
	else 
	{
		result->second.state = keycodeState;
	}
}