#pragma once
#include <map>
#include "vector2.h"
#include "GLFW/glfw3.h"

namespace spring
{
	using namespace std; 

	enum InputState
	{
		STATE_IDLE,
		STATE_DOWN,
		STATE_UP,
		STATE_DBCLICK,
		STATE_PRESS
	};

	enum MouseID : char
	{
		MOUSE_LEFT,
		MOUSE_RIGHT,
		MOUSE_WHEEL
	};

	class MouseInfo 
	{
	public:
		MouseID mouseID;
		InputState state = InputState::STATE_IDLE;
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

	enum KeyCode : int
	{
		Space = 32,
		Apostrophe = 39,  /* ' */
		Comma = 44,  /* , */
		Minus = 45,  /* - */
		Period = 46,  /* . */
		Slash = 47,  /* / */
		Number0 = 48,
		Number1 = 49,
		Number2 = 50,
		Number3 = 51,
		Number4 = 52,
		Number5 = 53,
		Number6 = 54,
		Number7 = 55,
		Number8 = 56,
		Number9 = 57,
		Semicolon = 59,  /* ; */
		Equal = 61,  /* = */
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LeftBracket = 91,  /* [ */
		BackSlash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96, /* ` */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		KeyPad0 = 320,
		KeyPad1 = 321,
		KeyPad2 = 322,
		KeyPad3 = 323,
		KeyPad4 = 324,
		KeyPad5 = 325,
		KeyPad6 = 326,
		KeyPad7 = 327,
		KeyPad8 = 328,
		KeyPad9 = 329,
		KeyPadDecimal = 330,
		KeyPadDivide = 331,
		KeyPadMultiply = 332,
		KeyPadSubtract = 333,
		KeyPadAdd = 334,
		KeyPadEnter = 335,
		KeyPadEqual = 336,
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348,
	};

	class KeyCodeInfo
	{
	public:
		KeyCode keyCode;
		InputState state = InputState::STATE_IDLE;
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

		static GLFWwindow* window;
	public:
		static Vector2 mousePosition;
		static Vector2 mouseDelta;
		static float mouseWheelDelta;

		static bool GetMouseDown(MouseID mouseId);
		static bool GetMouse(MouseID mouseId);
		static bool GetMouseUp(MouseID mouseId);
		static void setMouseState(MouseID mouseID, InputState state);
		static void setMousePosition(float xPos,float yPos);

		static bool GetKey(KeyCode keyCode);
		static bool GetKeyDown(KeyCode keyCode);
		static bool GetKeyUp(KeyCode keyCode);
		static void setKeyCodeState(KeyCode keyCode, InputState state);

		static float GetMouseWheel();
		static void setMouseWheel(float delta);

		static void InitializeInput(GLFWwindow* window);
	};
}