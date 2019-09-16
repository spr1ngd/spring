
#define _CRT_SECURE_NO_WARNINGS 

#include <windows.h>
#include <stdio.h> 
#include "glew.h"
#include "wglew.h"
#include <gl/GL.h> 

// spring engine
#include "spring.h"
#include "console.h"
#include "timer.h"
#include "mathf.h"
#include "screen.h"
#include "environment.h"
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
#include "light.h"

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

	Application app;
	app.Initialize(); 

#pragma region directional light 

	Environment::ambient.color = Color(75,75,75,255);

	Light* light = new Light();
	light->type = Light::Type::Spot;
	light->name = "Scene Light";
	light->color = Color(255, 244, 214, 255);
	light->intensity = 1.0f;
	light->transform->eulerangle = Vector3::bottom;
	light->transform->position = Vector3(0.0f,20.0f,0.0f);

#pragma endregion

#pragma region scene camera setting

	Camera camera;
	camera.clearFlag = Camera::ClearFlag::SolidColor;
	camera.transform->position = Vector3(6.0f,6.0f,6.0f);
	camera.center = new Vector3(0.0f,0.0f,0.0f);
	camera.background = Color(31,113,113,255);

#pragma endregion

#pragma region skybox rendering

	Material skyboxMaterial("res/shader/skybox/6 Sided.vs", "res/shader/skybox/6 Sided.fs");
	spring::Skybox skybox("6 Sided", &skyboxMaterial);
	skybox.Init();

#pragma endregion

#pragma region draw triangle by encapsuled object

	OrbitCamera orbitCamera;

	Material lightModelMat("res/shader/unlit/color.vs", "res/shader/unlit/color.fs");
	Model lightModel("res/model/obj/cube.obj");
	lightModel.material = &lightModelMat;
	lightModel.Init();
	lightModel.transform->scale = Vector3(.3f);
	lightModel.transform->position = light->transform->position;
	lightModel.material->shader->setColor(MAIN_COLOR, Color::yellow);

	spring::Material material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/diffuse.fs");
	Model model("res/model/fbx/sphere.fbx");
	model.material = &material;
	model.Init();
	model.transform->position = Vector3(0.0f, 0.0f, 0.0f);
	model.transform->scale = Vector3(3.0f);
	// model.transform->eulerangle = Vector3(-90.0f, 0.0f, 0.0f);
	model.material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 255));

#pragma endregion

	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Awake(); 

	float timer = 0.0f;

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
				
		// use this camera render scene objects.
		camera.Render();

		// 物体旋转
		model.transform->eulerangle.y += 2.0f;

		// 灯上下移动
		timer += Timer::deltaTime;
		float offset = Mathf::Cos(timer) * 3.0f + 5.0f;
		light->transform->position = Vector3(0, offset, 0);
		lightModel.transform->position = light->transform->position;

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