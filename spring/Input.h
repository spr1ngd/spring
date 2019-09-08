#pragma once
#include <map>

namespace spring
{
	using namespace std;

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
		KeyCodeState state = Idle;
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

	class Input
	{
	private:
		static map<KeyCode, KeyCodeInfo> keyCodeCaches;
		static KeyCodeInfo* GetKeyCodeInfo(KeyCode keycode);
	public:

		/*	static bool GetMouseDown( MouseID mouseId );
			static bool GetMouse( MouseID mouseId );
			static bool GetMouseUp( MouseID mouseId );*/

		static bool GetKey(KeyCode keyCode);
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);

		static void setKeyCodeState(KeyCode keyCode, KeyCodeState state);
	};
}