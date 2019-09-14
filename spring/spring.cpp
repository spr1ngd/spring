
#define _CRT_SECURE_NO_WARNINGS 

#include <windows.h>
#include <stdio.h> 
#include "glew.h"
#include "wglew.h"
#include <gl/GL.h> 

// spring engine
#include "spring.h"
#include "screen.h"
#include "application.h"
#include "shader.h"
#include "model.h"
#include "mesh.h"
#include "material.h"
#include "camera.h"
#include "behaviour.h"
#include "vertex.h"
#include "input.h"
#include "renderable.h"
#include "skybox.h"
#include "console.h"

// spring engine editor 
#include "orbitcamera.h"
#include "fps.h"

#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib")

using namespace spring;
using namespace spring::editor;

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	float x = LOWORD(lParam);
	float y = HIWORD(lParam);

	// todo : x , y is the mouse position in screen 

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

		break;

#pragma endregion

#pragma region keyboard 

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A':
			Input::setKeyCodeState(KeyCode::A, InputState::Down);
			break;
		case 'W':
			Input::setKeyCodeState(KeyCode::W, InputState::Down);
			break;
		case 'D':
			Input::setKeyCodeState(KeyCode::D, InputState::Down);
			break;
		case 'S':
			Input::setKeyCodeState(KeyCode::S, InputState::Down);
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
		case 'W':
			Input::setKeyCodeState(KeyCode::W, InputState::Up);
			break;
		case 'D':
			Input::setKeyCodeState(KeyCode::D, InputState::Up);
			break;
		case 'S':
			Input::setKeyCodeState(KeyCode::S, InputState::Up);
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

	Application app;
	app.Initialize();

#pragma region scene camera setting

	Camera camera;
	//camera.transform->position = Vector3(.5f,.5f,.5f);
	camera.transform->position = Vector3::zero;

#pragma endregion


#pragma region skybox rendering

	Material skyboxMaterial("res/shader/skybox/6 Sided.vs","res/shader/skybox/6 Sided.fs");
	//  Material skyboxMaterial("res/shader/base/base.vs", "res/shader/base/base.fs");
	//Skybox skybox("6 Sided",&skyboxMaterial);
	//skybox.Init();

#pragma endregion

#pragma region draw triangle by encapsuled object

	OrbitCamera orbitCamera;

	//spring::Material material("res/shader/base/base.vs", "res/shader/base/base.fs");
	spring::Material material("res/shader/vertex/vertexcolor.vs","res/shader/vertex/vertexcolor.fs");
	Model model("res/model/obj/Cube.obj");
	//Model model("res/model/fbx/tauren.fbx");
	model.material = &material;
	model.Init();
	model.transform->position.z = -0.3f;
	model.transform->scale = Vector3(1.0f);

#pragma endregion

	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Awake();

	// glDisable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_FRONT);
	// glEnable(GL_DEPTH_TEST);
	// glPolygonMode(GL_BACK,GL_LINE);

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
				
		// use this camera render scene objects.
		camera.Render();

		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->Update();

		// note : draw all object inherited Renderable.
		Renderable::Draw();
		// FPS::CalculateFramePerSecond();

		glFinish();
		SwapBuffers(dc);
	}
	return  0;
}