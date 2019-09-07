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
	};

	class Input
	{
	private:
		map<KeyCode, KeyCodeInfo> keyCodeCaches;
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