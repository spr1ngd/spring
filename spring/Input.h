#pragma once
#include <map>

namespace spring
{
	using namespace std;

#pragma region mouse events

	enum MouseID : char
	{
		LEFT,
		RIGHT,
		WHELL
	};
	enum MouseState 
	{
		Idle,
		Down,
		Up
	};
	class MouseInfo 
	{
	public:
		MouseID mouseID;
		MouseState state = MouseState::Idle;
		bool down = false;
		bool up = false;
	public:
		MouseInfo();
		MouseInfo( MouseID mouseID,MouseState state )   
		{
			this->mouseID = mouseID;
			this->state = state;
		}
	};

#pragma endregion

#pragma region key board events

	enum KeyCode : char
	{
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		W = 'W',
		S = 'S'
	};
	enum KeyCodeState
	{
		Idle,
		Down,
		Up
	};
	class KeyCodeInfo
	{
	public:
		KeyCode keyCode;
		KeyCodeState state = KeyCodeState::Idle;
		bool down = false;
		bool up = false;
	public:
		KeyCodeInfo();
		KeyCodeInfo(KeyCode keyCode, KeyCodeState state) 
		{
			this->keyCode = keyCode;
			this->state = state;
		}
	};

#pragma endregion


	class Input
	{
	private:
		static map<KeyCode, KeyCodeInfo> keyCodeCaches;
		static KeyCodeInfo* GetKeyCodeInfo(KeyCode keycode);

		static map<MouseID, MouseInfo> mouseCaches;
		static MouseInfo* GetMouseInfo(MouseID mouseID);
	public:

		static bool GetMouseDown(MouseID mouseId);
		static bool GetMouse(MouseID mouseId);
		static bool GetMouseUp(MouseID mouseId);

		static bool GetKey(KeyCode keyCode);
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);

		static void setKeyCodeState(KeyCode keyCode, KeyCodeState state);
		static void setMouseState(MouseID mouseID, MouseState state);
	};
}