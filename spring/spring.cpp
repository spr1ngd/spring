
#include <windows.h>
#include <stdio.h> 
#include "glew.h"
#include "wglew.h"
#include <gl/GL.h>
#include "spring.h"
#include "application.h"
#include "shader.h"
#include "model.h"
#include "mesh.h"
#include "material.h"
#include "camera.h"
#include "behaviour.h"

#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib")

using namespace spring;

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
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
	rect.right = (long)800.0;
	rect.top = (long)0.0;
	rect.bottom = (long)600.0;
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

#pragma region draw triangle by encapsuled object

	Camera camera;

	spring::Mesh mesh;
	/*mesh.vertices =
	{
		spring::Vector3(0.5f,0.5f,0.0f),
		spring::Vector3(0.5f, -0.5f, 0.0f),
		spring::Vector3(-0.5f, -0.5f, 0.0f),
		spring::Vector3(-0.5f, 0.5f, 0.0f)
	};
	mesh.indices = {0,1,3,1,2,3};*/
	/*mesh.indexCount = 6;
	mesh.vertexCount = 12;*/ 

	//spring::Material material("res/shader/base/base.vs", "res/shader/base/base.fs");
	spring::Material material("res/shader/vertex/vertexcolor.vs","res/shader/vertex/vertexcolor.fs");

	/*spring::Model model(&mesh, &material);
	
	model.Init();*/
	//Model model("res/model/fbx/tauren.fbx");
	Model model("res/model/obj/Cube.obj");
	model.material = &material;
	model.Init();
	model.transform->position.z = -10.0f;

#pragma endregion

	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Awake();

	glDisable(GL_CULL_FACE);

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

		glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

		// todo : does not use camera to render object, render object by  spring engine, if need view matrix and projection matrix, get current render camera by interface.
		camera.Render(&model);
		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->Update();
		glFinish();
		SwapBuffers(dc);
	}
	return  0;
}