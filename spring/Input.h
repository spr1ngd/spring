#pragma once
#include <map>
#include "vector2.h"

namespace spring
{
	using namespace std; 

	enum InputState
	{
		Idle,
		Down,
		Up,
		DBClick
	};

	enum MouseID : char
	{
		LEFT,
		RIGHT,
		WHELL
	};
	class MouseInfo 
	{
	public:
		MouseID mouseID;
		InputState state = InputState::Idle;
		bool down = false;
		bool up = false;
		float wheelDelta = 0.0f;
	public:
		MouseInfo();
		MouseInfo( MouseID mouseID, InputState state )
		{
			this->mouseID = mouseID;
			this->state = state;
		}
	}; 

	enum KeyCode : char
	{
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z'
	};

	class KeyCodeInfo
	{
	public:
		KeyCode keyCode;
		InputState state = InputState::Idle;
		bool down = false;
		bool up = false;
	public:
		KeyCodeInfo();
		KeyCodeInfo(KeyCode keyCode, InputState state) 
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

		static map<MouseID, MouseInfo> mouseCaches;
		static MouseInfo* GetMouseInfo(MouseID mouseID);
	public:
		static Vector2 mousePosition;
		static Vector2 mouseDelta;
		static float mouseWheelDelta;

		static bool GetMouseDown(MouseID mouseId);
		static bool GetMouse(MouseID mouseId);
		static bool GetMouseUp(MouseID mouseId);

		static bool GetKey(KeyCode keyCode);
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);
		static float GetMouseWheel();

		static void setKeyCodeState(KeyCode keyCode, InputState state);
		static void setMouseState(MouseID mouseID, InputState state);
		static void setMouseWheel(float delta);

		static void setMousePosition(float xPos,float yPos);
	};
}