
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
#include "modelloader.h"
#include "shader.h"
#include "meshrenderer.h"
#include "mesh.h"
#include "material.h"
#include "camera.h"
#include "behaviour.h"
#include "vertex.h"
#include "input.h"
#include "renderable.h"
#include "skybox.h"
#include "light.h"
#include "axishelper.h"

// spring engine editor 
#include "orbitcamera.h"
#include "firstplayercamera.h"
#include "fps.h"

#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib")

using namespace spring;
using namespace spring::editor;

LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
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
		Input::mousePosition = Vector2(xPos, yPos);
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
		float xPos = LOWORD(lParam);
		float yPos = HIWORD(lParam);
		Input::mousePosition = Vector2(xPos,yPos);
		Input::mouseWheelDelta = delta;
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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Application app;
	app.Initialize(); 

	auto createLight = [&]( Light::Type lightType,Color lightColor ,float intensity ,Vector3 position,Vector3 eulerangle )
	{
		Light* light = new Light();
		light->type = lightType;
		light->color = lightColor;
		light->intensity = intensity;
		light->transform->eulerangle = eulerangle;
		light->transform->position = position;
		return light;
	};

	//Color(255, 244, 214, 255)
#pragma region directional light 

	Environment::ambient.color = Color(75,75,75,255);

	Light* light = createLight(Light::Type::Directional, Color(255, 244, 214, 255), 0.7f, Vector3(10.0f, 10.0f, 10.0f), Vector3::down);
	//Light* pointLigh1 = createLight(Light::Type::Point, Color::red, 0.6f, Vector3(5.0f, 0.0f, 0.0f), Vector3::left);
	//Light* pointLigh2 = createLight(Light::Type::Point, Color::green, 0.6f, Vector3(-5.0f, 0.0f, 0.0f), Vector3::right);
	//Light* pointLigh3 = createLight(Light::Type::Point, Color::blue, 0.6f, Vector3(0.0f, 0.0f, 5.0f), Vector3::back);
	//Light* pointLigh4 = createLight(Light::Type::Point, Color::green, 0.6f, Vector3(0.0f, 0.0f, -5.0f), Vector3::forward);
	//Light* spotLight = createLight(Light::Type::Spot, Color::yellow, 1.3f, Vector3(0.0f, 6.0f, 0.0f), Vector3::bottom);

#pragma endregion

#pragma region scene camera setting

	Camera camera;
	camera.clearFlag = Camera::ClearFlag::Skybox;
	camera.transform->position = Vector3(1.0f,1.0f,1.0f);
	camera.center = Vector3(0.0f,0.0f,0.0f);
	camera.background = Color(31,113,113,255);

#pragma endregion

#pragma region scene gizmos 

	// axis
	AxisHelper axishelper;
	axishelper.Render();
		
#pragma endregion


#pragma region skybox rendering

	Material skyboxMaterial("res/shader/skybox/6 Sided.vs", "res/shader/skybox/6 Sided.fs");
	spring::Skybox skybox("6 Sided", &skyboxMaterial);
	skybox.Init();

#pragma endregion

#pragma region draw triangle by encapsuled object

	//FirstPlayerCamera firstplayer;//todo : test it working state.
	//firstplayer.moveSpeed = 0.1f;

	OrbitCamera orbit;
	orbit.target = Vector3::zero;
	orbit.zoomSpeed = 0.05f;

	// draw floor
	//ModelLoader floorLoader = ModelLoader();
	//floorLoader.Load("res/model/obj/quad.obj");
	//Material floorMaterial("res/shader/diffuse/diffuse.vs","res/shader/diffuse/diffuse.fs");
	//floorMaterial.name = "floor";
	//MeshRenderer floor(&floorMaterial);
	//floor.meshes = floorLoader.meshes;
	//floor.Init();
	//floor.transform->scale = Vector3(8.0f,8.0f,8.0f);
	//floor.transform->eulerangle = Vector3(-90.0f,0.0f,0.0f);

	// draw light model
	ModelLoader loader = ModelLoader();
	loader.Load("res/model/obj/cube.obj");
	Material lightModelMat("res/shader/unlit/color.vs", "res/shader/unlit/color.fs");
	lightModelMat.name = "color";
	MeshRenderer lightModel(&lightModelMat);
	lightModel.meshes = loader.meshes;
	lightModel.textures = loader.loadedTextures;
	lightModel.Init();
	lightModel.transform->scale = Vector3(.3f);
	// lightModel.transform->position = spotLight->transform->position;
	lightModel.material->shader->setColor(MAIN_COLOR, Color::yellow);

	// draw a sphere
	

	// TextureLoader textureLoader;
	// GLuint texture = textureLoader.Load("res/texture/carbon_fiber.jpg");
	// model.material->shader->setTexture("MainTextureData.texture", texture);
	// model.material->shader->setTilling("MainTextureData.texture", Vector2(10.0f,10.0f));

	ModelLoader modelLoader = ModelLoader();
	modelLoader.Load("res/model/fbx/sphere.fbx");

	// todo : delete pointers
	vector<Material*> mats;
	vector<MeshRenderer*> renderers;

	int sphereCount = 1;
	for (int i = 0; i < sphereCount; i++)
	{
		for (int j = 0; j < sphereCount; j++)
		{
			Material* mat = new Material("res/shader/diffuse/diffuse.vs", "res/shader/diffuse/transparency.fs");
			mat->name = "diffuse";
			mat->renderMode = Material::Fill;
			mats.push_back(mat);

			MeshRenderer*meshRenderer = new MeshRenderer(mat);
			meshRenderer->meshes = modelLoader.meshes;
			meshRenderer->textures = modelLoader.loadedTextures;
			meshRenderer->material->cullface = Material::CullFace::Back;
			meshRenderer->Init();
			meshRenderer->transform->position = Vector3(-10.0f + i * 2.0f, 0.0, -10.0f + j * 2.0f);
			meshRenderer->transform->scale = Vector3(1.0f);
			meshRenderer->transform->eulerangle = Vector3(-90.0f, 0.0f, 0.0f);
			meshRenderer->material->shader->setColor(MAIN_COLOR, Color(204, 204, 204, 128));
			meshRenderer->material->shader->setColor("Specular_Color", Color::white);
			meshRenderer->material->shader->setFloat("Specular_Intensity", 1.0f);
			meshRenderer->material->shader->setFloat("Specular_Attenuation", 64.0f);
			renderers.push_back(meshRenderer);
		}
	}

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
				
		// update camera state
		camera.Render();

		// 物体旋转
		// model.transform->eulerangle.x += 2.0f;

		// 灯上下移动
		timer += Timer::deltaTime;
		float offset = Mathf::Cos(timer) * 3.0f + 5.0f;
		/*spotLight->transform->position = Vector3(0, offset, 0);
		lightModel.transform->position = spotLight->transform->position;*/
		skybox.transform->position = Camera::main->transform->position;
		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->Update();

		// note : draw all object inherited Renderable.
		Renderable::Draw();
		// FPS::CalculateFramePerSecond();

		// reset mouse wheel delta 
		Input::setMouseWheel(0.0f);
		glFinish();
		SwapBuffers(dc);
	}
	return  0;
}