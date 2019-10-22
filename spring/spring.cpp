﻿
#define _CRT_SECURE_NO_WARNINGS 

#include <windows.h>
#include <stdio.h> 
#include "glew.h"
#include "wglew.h"
#include <gl/GL.h> 
#include "springengine.h"
#include "spring.h"
#include "sample.h"
#include "vector2.h"

// spring engine
#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib")

using namespace spring;
using namespace spring::editor;

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{  
	// Input::setMousePosition(Input::mousePosition.x,Input::mousePosition.y);
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

#pragma region mouse left button

	case WM_LBUTTONDBLCLK:
		Input::setMouseState(MouseID::LEFT, InputState::DBClick);
		break;
	case WM_LBUTTONDOWN:
		Input::setMouseState(MouseID::LEFT, InputState::Down);
		break;
	case WM_LBUTTONUP:
		Input::setMouseState(MouseID::LEFT, InputState::Up);
		break;

#pragma endregion

#pragma region mouse right button


	case WM_RBUTTONDBLCLK:
		Input::setMouseState(MouseID::RIGHT, InputState::DBClick);
		break;
	case WM_RBUTTONDOWN:
		Input::setMouseState(MouseID::RIGHT, InputState::Down);
		break;
	case WM_RBUTTONUP:
		Input::setMouseState(MouseID::RIGHT, InputState::Up);
		break;

#pragma endregion

#pragma region mouse move

	case WM_MOUSEMOVE:
	{
		float xPos = LOWORD(lParam);
		float yPos = HIWORD(lParam);
		Input::setMousePosition(xPos, yPos);
	}
	break;

#pragma endregion

#pragma region mouse wheel event

	case WM_MBUTTONDBLCLK:
		Input::setMouseState(MouseID::WHELL, InputState::DBClick);
		break;
	case WM_MBUTTONDOWN:
		Input::setMouseState(MouseID::WHELL, InputState::Down);
		break;
	case WM_MBUTTONUP:
		Input::setMouseState(MouseID::WHELL, InputState::Up);
		break;

	case WM_MOUSEWHEEL:
	{
		float fwKey = LOWORD(wParam);
		float delta = (short)HIWORD(wParam) / 120.0f; // windows API return value is multiple of 120
		/*float xPos = LOWORD(lParam);
		float yPos = HIWORD(lParam);
		Input::setMousePosition(xPos, yPos);*/
		Input::setMouseWheel(delta);
	}
	break;

#pragma endregion

#pragma region keyboard 

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			Input::setKeyCodeState(KeyCode::A, InputState::Down);
			break;
		case 'B':
			Input::setKeyCodeState(KeyCode::B, InputState::Down);
			break;
		case 'C':
			Input::setKeyCodeState(KeyCode::C, InputState::Down);
			break;
		case 'D':
			Input::setKeyCodeState(KeyCode::D, InputState::Down);
			break;
		case 'E':
			Input::setKeyCodeState(KeyCode::E, InputState::Down);
			break;
		case 'F':
			Input::setKeyCodeState(KeyCode::F, InputState::Down);
			break;
		case 'G':
			Input::setKeyCodeState(KeyCode::G, InputState::Down);
			break;
		case 'H':
			Input::setKeyCodeState(KeyCode::H, InputState::Down);
			break;
		case 'I':
			Input::setKeyCodeState(KeyCode::I, InputState::Down);
			break;
		case 'J':
			Input::setKeyCodeState(KeyCode::J, InputState::Down);
			break;
		case 'K':
			Input::setKeyCodeState(KeyCode::K, InputState::Down);
			break;
		case 'L':
			Input::setKeyCodeState(KeyCode::L, InputState::Down);
			break;
		case 'M':
			Input::setKeyCodeState(KeyCode::M, InputState::Down);
			break;
		case 'N':
			Input::setKeyCodeState(KeyCode::N, InputState::Down);
			break;
		case 'O':
			Input::setKeyCodeState(KeyCode::O, InputState::Down);
			break;
		case 'P':
			Input::setKeyCodeState(KeyCode::P, InputState::Down);
			break;
		case 'Q':
			Input::setKeyCodeState(KeyCode::Q, InputState::Down);
			break;
		case 'R':
			Input::setKeyCodeState(KeyCode::R, InputState::Down);
			break;
		case 'S':
			Input::setKeyCodeState(KeyCode::S, InputState::Down);
			break;
		case 'T':
			Input::setKeyCodeState(KeyCode::T, InputState::Down);
			break;
		case 'U':
			Input::setKeyCodeState(KeyCode::U, InputState::Down);
			break;
		case 'V':
			Input::setKeyCodeState(KeyCode::V, InputState::Down);
			break;
		case 'W':
			Input::setKeyCodeState(KeyCode::W, InputState::Down);
			break;
		case 'X':
			Input::setKeyCodeState(KeyCode::X, InputState::Down);
			break;
		case 'Y':
			Input::setKeyCodeState(KeyCode::Y, InputState::Down);
			break;
		case 'Z':
			Input::setKeyCodeState(KeyCode::Z, InputState::Down);
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'A':
			Input::setKeyCodeState(KeyCode::A, InputState::Up);
			break;
		case 'B':
			Input::setKeyCodeState(KeyCode::B, InputState::Up);
			break;
		case 'C':
			Input::setKeyCodeState(KeyCode::C, InputState::Up);
			break;
		case 'D':
			Input::setKeyCodeState(KeyCode::D, InputState::Up);
			break;
		case 'E':
			Input::setKeyCodeState(KeyCode::E, InputState::Up);
			break;
		case 'F':
			Input::setKeyCodeState(KeyCode::F, InputState::Up);
			break;
		case 'G':
			Input::setKeyCodeState(KeyCode::G, InputState::Up);
			break;
		case 'H':
			Input::setKeyCodeState(KeyCode::H, InputState::Up);
			break;
		case 'I':
			Input::setKeyCodeState(KeyCode::I, InputState::Up);
			break;
		case 'J':
			Input::setKeyCodeState(KeyCode::J, InputState::Up);
			break;
		case 'K':
			Input::setKeyCodeState(KeyCode::K, InputState::Up);
			break;
		case 'L':
			Input::setKeyCodeState(KeyCode::L, InputState::Up);
			break;
		case 'M':
			Input::setKeyCodeState(KeyCode::M, InputState::Up);
			break;
		case 'N':
			Input::setKeyCodeState(KeyCode::N, InputState::Up);
			break;
		case 'O':
			Input::setKeyCodeState(KeyCode::O, InputState::Up);
			break;
		case 'P':
			Input::setKeyCodeState(KeyCode::P, InputState::Up);
			break;
		case 'Q':
			Input::setKeyCodeState(KeyCode::Q, InputState::Up);
			break;
		case 'R':
			Input::setKeyCodeState(KeyCode::R, InputState::Up);
			break;
		case 'S':
			Input::setKeyCodeState(KeyCode::S, InputState::Up);
			break;
		case 'T':
			Input::setKeyCodeState(KeyCode::T, InputState::Up);
			break;
		case 'U':
			Input::setKeyCodeState(KeyCode::U, InputState::Up);
			break;
		case 'V':
			Input::setKeyCodeState(KeyCode::V, InputState::Up);
			break;
		case 'W':
			Input::setKeyCodeState(KeyCode::W, InputState::Up);
			break;
		case 'X':
			Input::setKeyCodeState(KeyCode::X, InputState::Up);
			break;
		case 'Y':
			Input::setKeyCodeState(KeyCode::Y, InputState::Up);
			break;
		case 'Z':
			Input::setKeyCodeState(KeyCode::Z, InputState::Up);
			break;
		default:
			break;
		}
		break;

#pragma endregion
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// initialize spring engine configuration.
	Screen::width = 800;
	Screen::height = 600;

	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = GLWindowProc;
	wndClass.lpszClassName = L"OpenGL";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	ATOM atom = RegisterClassEx(&wndClass);
	RECT rect;
	rect.left = (long)0.0;
	rect.right = (long)Screen::width;
	rect.top = (long)0.0;
	rect.bottom = (long)Screen::height;
	// AdjustWinwRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowEx(NULL, L"OpenGL", L"spring engine", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);

	HDC dc = GetDC(hwnd);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_TYPE_RGBA | PFD_DOUBLEBUFFER;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	int pixelFormatID = ChoosePixelFormat(dc, &pfd);
	SetPixelFormat(dc, pixelFormatID, &pfd);
	HGLRC rc = wglCreateContext(dc);
	wglMakeCurrent(dc, rc);
	glewInit();

	MSG msg;

	// call the console window.
	AllocConsole();
	SetConsoleCtrlHandler(NULL, true);
	freopen("CONOUT$", "w", stdout);

	int width, height;
	GetClientRect(hwnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	glClearColor(41.0f / 255.0f, 71.0f / 255.0f, 121.0f / 255.0f, 1.0f);
	glViewport(0, 0, width, height);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	glEnable(GL_MULTISAMPLE);
// 	glEnable(GL_BLEND);
// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// draw sample scene
	Sample* sample = new Sample();

	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Awake(); 
	Timer::Start();

	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				for (auto behaviour : Behaviour::behaviours)
					behaviour.second->Destroy();
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 

		Timer::Time();
		Gizmos::Render();
		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->Update();
		Renderable::Draw();
		// FPS::CalculateFramePerSecond();
		Input::setMouseWheel(0.0f);
		Input::mouseDelta = Vector2::zero;

		glFinish();
		SwapBuffers(dc);
	}
	return  0;
}