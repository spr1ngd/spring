//
//#define _CRT_SECURE_NO_WARNINGS 
//
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//
//#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
//#include <GL/gl3w.h>    // Initialize with gl3wInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
////#include <GL/glew.h>    // Initialize with glewInit()
//#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
//#include <glad/glad.h>  // Initialize with gladLoadGL()
//#else
//#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
//#endif
//
//#include <windows.h>
//#include <stdio.h> 
//#include "glew.h"
//#include "wglew.h"
//#include <gl/GL.h>
//#include "GLFW/glfw3.h"
//#include "springengine.h"
//#include "spring.h"
//#include "sample.h"
//#include "vector2.h"
//#include "postprocessing.h"
//
//// spring engine
//#pragma comment (lib,"glfw3.lib")
//#pragma comment (lib,"glew32.lib")
//#pragma comment (lib,"opengl32.lib")
//
//using namespace spring;
//using namespace spring::editor;
//
//LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{  
//	// Input::setMousePosition(Input::mousePosition.x,Input::mousePosition.y);
//	switch (msg)
//	{
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		break;
//
//#pragma region mouse left button
//
//	case WM_LBUTTONDBLCLK:
//		Input::setMouseState(MouseID::LEFT, InputState::DBClick);
//		break;
//	case WM_LBUTTONDOWN:
//		Input::setMouseState(MouseID::LEFT, InputState::Down);
//		break;
//	case WM_LBUTTONUP:
//		Input::setMouseState(MouseID::LEFT, InputState::Up);
//		break;
//
//#pragma endregion
//
//#pragma region mouse right button
//
//
//	case WM_RBUTTONDBLCLK:
//		Input::setMouseState(MouseID::RIGHT, InputState::DBClick);
//		break;
//	case WM_RBUTTONDOWN:
//		Input::setMouseState(MouseID::RIGHT, InputState::Down);
//		break;
//	case WM_RBUTTONUP:
//		Input::setMouseState(MouseID::RIGHT, InputState::Up);
//		break;
//
//#pragma endregion
//
//#pragma region mouse move
//
//	case WM_MOUSEMOVE:
//	{
//		float xPos = LOWORD(lParam);
//		float yPos = HIWORD(lParam);
//		Input::setMousePosition(xPos, yPos);
//	}
//	break;
//
//#pragma endregion
//
//#pragma region mouse wheel event
//
//	case WM_MBUTTONDBLCLK:
//		Input::setMouseState(MouseID::WHELL, InputState::DBClick);
//		break;
//	case WM_MBUTTONDOWN:
//		Input::setMouseState(MouseID::WHELL, InputState::Down);
//		break;
//	case WM_MBUTTONUP:
//		Input::setMouseState(MouseID::WHELL, InputState::Up);
//		break;
//
//	case WM_MOUSEWHEEL:
//	{
//		float fwKey = LOWORD(wParam);
//		float delta = (short)HIWORD(wParam) / 120.0f; // windows API return value is multiple of 120
//		/*float xPos = LOWORD(lParam);
//		float yPos = HIWORD(lParam);
//		Input::setMousePosition(xPos, yPos);*/
//		Input::setMouseWheel(delta);
//	}
//	break;
//
//#pragma endregion
//
//#pragma region keyboard 
//
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case 'A':
//			Input::setKeyCodeState(KeyCode::A, InputState::Down);
//			break;
//		case 'B':
//			Input::setKeyCodeState(KeyCode::B, InputState::Down);
//			break;
//		case 'C':
//			Input::setKeyCodeState(KeyCode::C, InputState::Down);
//			break;
//		case 'D':
//			Input::setKeyCodeState(KeyCode::D, InputState::Down);
//			break;
//		case 'E':
//			Input::setKeyCodeState(KeyCode::E, InputState::Down);
//			break;
//		case 'F':
//			Input::setKeyCodeState(KeyCode::F, InputState::Down);
//			break;
//		case 'G':
//			Input::setKeyCodeState(KeyCode::G, InputState::Down);
//			break;
//		case 'H':
//			Input::setKeyCodeState(KeyCode::H, InputState::Down);
//			break;
//		case 'I':
//			Input::setKeyCodeState(KeyCode::I, InputState::Down);
//			break;
//		case 'J':
//			Input::setKeyCodeState(KeyCode::J, InputState::Down);
//			break;
//		case 'K':
//			Input::setKeyCodeState(KeyCode::K, InputState::Down);
//			break;
//		case 'L':
//			Input::setKeyCodeState(KeyCode::L, InputState::Down);
//			break;
//		case 'M':
//			Input::setKeyCodeState(KeyCode::M, InputState::Down);
//			break;
//		case 'N':
//			Input::setKeyCodeState(KeyCode::N, InputState::Down);
//			break;
//		case 'O':
//			Input::setKeyCodeState(KeyCode::O, InputState::Down);
//			break;
//		case 'P':
//			Input::setKeyCodeState(KeyCode::P, InputState::Down);
//			break;
//		case 'Q':
//			Input::setKeyCodeState(KeyCode::Q, InputState::Down);
//			break;
//		case 'R':
//			Input::setKeyCodeState(KeyCode::R, InputState::Down);
//			break;
//		case 'S':
//			Input::setKeyCodeState(KeyCode::S, InputState::Down);
//			break;
//		case 'T':
//			Input::setKeyCodeState(KeyCode::T, InputState::Down);
//			break;
//		case 'U':
//			Input::setKeyCodeState(KeyCode::U, InputState::Down);
//			break;
//		case 'V':
//			Input::setKeyCodeState(KeyCode::V, InputState::Down);
//			break;
//		case 'W':
//			Input::setKeyCodeState(KeyCode::W, InputState::Down);
//			break;
//		case 'X':
//			Input::setKeyCodeState(KeyCode::X, InputState::Down);
//			break;
//		case 'Y':
//			Input::setKeyCodeState(KeyCode::Y, InputState::Down);
//			break;
//		case 'Z':
//			Input::setKeyCodeState(KeyCode::Z, InputState::Down);
//			break;
//		default:
//			break;
//		}
//		break;
//	case WM_KEYUP:
//		switch (wParam)
//		{
//		case 'A':
//			Input::setKeyCodeState(KeyCode::A, InputState::Up);
//			break;
//		case 'B':
//			Input::setKeyCodeState(KeyCode::B, InputState::Up);
//			break;
//		case 'C':
//			Input::setKeyCodeState(KeyCode::C, InputState::Up);
//			break;
//		case 'D':
//			Input::setKeyCodeState(KeyCode::D, InputState::Up);
//			break;
//		case 'E':
//			Input::setKeyCodeState(KeyCode::E, InputState::Up);
//			break;
//		case 'F':
//			Input::setKeyCodeState(KeyCode::F, InputState::Up);
//			break;
//		case 'G':
//			Input::setKeyCodeState(KeyCode::G, InputState::Up);
//			break;
//		case 'H':
//			Input::setKeyCodeState(KeyCode::H, InputState::Up);
//			break;
//		case 'I':
//			Input::setKeyCodeState(KeyCode::I, InputState::Up);
//			break;
//		case 'J':
//			Input::setKeyCodeState(KeyCode::J, InputState::Up);
//			break;
//		case 'K':
//			Input::setKeyCodeState(KeyCode::K, InputState::Up);
//			break;
//		case 'L':
//			Input::setKeyCodeState(KeyCode::L, InputState::Up);
//			break;
//		case 'M':
//			Input::setKeyCodeState(KeyCode::M, InputState::Up);
//			break;
//		case 'N':
//			Input::setKeyCodeState(KeyCode::N, InputState::Up);
//			break;
//		case 'O':
//			Input::setKeyCodeState(KeyCode::O, InputState::Up);
//			break;
//		case 'P':
//			Input::setKeyCodeState(KeyCode::P, InputState::Up);
//			break;
//		case 'Q':
//			Input::setKeyCodeState(KeyCode::Q, InputState::Up);
//			break;
//		case 'R':
//			Input::setKeyCodeState(KeyCode::R, InputState::Up);
//			break;
//		case 'S':
//			Input::setKeyCodeState(KeyCode::S, InputState::Up);
//			break;
//		case 'T':
//			Input::setKeyCodeState(KeyCode::T, InputState::Up);
//			break;
//		case 'U':
//			Input::setKeyCodeState(KeyCode::U, InputState::Up);
//			break;
//		case 'V':
//			Input::setKeyCodeState(KeyCode::V, InputState::Up);
//			break;
//		case 'W':
//			Input::setKeyCodeState(KeyCode::W, InputState::Up);
//			break;
//		case 'X':
//			Input::setKeyCodeState(KeyCode::X, InputState::Up);
//			break;
//		case 'Y':
//			Input::setKeyCodeState(KeyCode::Y, InputState::Up);
//			break;
//		case 'Z':
//			Input::setKeyCodeState(KeyCode::Z, InputState::Up);
//			break;
//		default:
//			break;
//		}
//		break;
//
//#pragma endregion
//	}
//	return DefWindowProc(hwnd, msg, wParam, lParam);
//}
//
//static void glfw_error_callback(int error, const char* description)
//{
//	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
//}
//
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
//{
//	// initialize spring engine configuration.
//	Screen::width = 800 + 16;
//	Screen::height = 600 + 39;
//
//	WNDCLASSEX wndClass;
//	wndClass.cbClsExtra = 0;
//	wndClass.cbSize = sizeof(WNDCLASSEX);
//	wndClass.cbWndExtra = 0;
//	wndClass.hbrBackground = NULL;
//	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndClass.hIcon = NULL;
//	wndClass.hIconSm = NULL;
//	wndClass.hInstance = hInstance;
//	wndClass.lpfnWndProc = GLWindowProc;
//	wndClass.lpszClassName = L"OpenGL";
//	wndClass.lpszMenuName = NULL;
//	wndClass.style = CS_VREDRAW | CS_HREDRAW;
//	ATOM atom = RegisterClassEx(&wndClass);
//	RECT rect;
//	rect.left = (long)0.0;
//	rect.right = (long)Screen::width;
//	rect.top = (long)0.0;
//	rect.bottom = (long)Screen::height;
//	// AdjustWinwRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
//
//	// todo : create a real fixed pixel count window.
//	HWND hwnd = CreateWindowEx(NULL, L"OpenGL", L"spring engine", WS_OVERLAPPEDWINDOW, 100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
//
//	HDC dc = GetDC(hwnd);
//	PIXELFORMATDESCRIPTOR pfd;
//	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
//	pfd.nVersion = 1;
//	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_TYPE_RGBA | PFD_DOUBLEBUFFER;
//	pfd.iLayerType = PFD_MAIN_PLANE;
//	pfd.iPixelType = PFD_TYPE_RGBA;
//	pfd.cColorBits = 32;
//	pfd.cDepthBits = 24;
//	pfd.cStencilBits = 8;
//
//	int pixelFormatID = ChoosePixelFormat(dc, &pfd);
//	SetPixelFormat(dc, pixelFormatID, &pfd);
//	HGLRC rc = wglCreateContext(dc);
//	wglMakeCurrent(dc, rc);
//
//	glewInit();
//	glEnable(GL_MULTISAMPLE);
//
//	MSG msg;
//
//	// call the console window.
//	AllocConsole();
//	SetConsoleCtrlHandler(NULL, true);
//	freopen("CONOUT$", "w", stdout);
//
//	int width, height;
//	GetClientRect(hwnd, &rect);
//	width = rect.right - rect.left;
//	height = rect.bottom - rect.top;
//
//	Screen::width = width;
//	Screen::height = height;
//	Screen::halfWidth = Screen::width / 2.0f;
//	Screen::halfHeight = Screen::height / 2.0f;
//
//	glClearColor(41.0f / 255.0f, 71.0f / 255.0f, 121.0f / 255.0f, 1.0f);
//	glViewport(0, 0, width, height);
//	ShowWindow(hwnd, SW_SHOW);
//	UpdateWindow(hwnd);
//
//	
//	// draw sample scene
//	Sample* sample = new Sample();
//
//	Timer::Start();
//	for (auto behaviour : Behaviour::behaviours)
//		behaviour.second->Awake(); 
//
//	unsigned int* uiRenderLayer = new unsigned int[1]{ Layer::UI };
//	unsigned int* defaultRenderLayer = new unsigned int[2]{ Layer::Default,Layer::Skybox };
//
//	Camera* uiCamera = new Camera();
//	uiCamera->name = "Internal UI Camera";
//	uiCamera->cullingMask->set(uiRenderLayer);
//	uiCamera->clearFlag = Camera::None; 
//
//	// 0. construct post processing instance.
//	class::PostProcessing* postProcessing = new class::PostProcessing();
//	postProcessing->enabled = true;
//	postProcessing->antiAliasing->enabled = false;
//	postProcessing->bloom->enabled = true;
//	postProcessing->PreProcess();
//
//	while (true)
//	{
//		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
//		{
//			AssetLoader::Release();
//			if (msg.message == WM_QUIT)
//			{
//				for (auto behaviour : Behaviour::behaviours)
//					behaviour.second->Destroy();
//				break;
//			}
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		} 
//		Timer::Time();
//		Gizmos::Render();
//
//		// 将灯光阴影优先渲染
//		Light::CastShadow();
//
//		// camera view/projection matrix calculation must be earlier than update method ,otherwise camera's position maybe update late than other transform.
//		for (vector<Camera*>::iterator cam = Camera::cameras.begin(); cam != Camera::cameras.end(); cam++)
//			(*cam)->Update();
//
//		for (auto behaviour : Behaviour::behaviours)
//			behaviour.second->Update(); 
//
//		for (auto behaviour : Behaviour::behaviours)
//			behaviour.second->OnPreRender(); 
//
//		// draw 3d scene.
//		for (vector<Camera*>::iterator cam = Camera::cameras.begin(); cam != Camera::cameras.end(); cam++)
//		{
//			Camera::current = *cam;
//			if (Camera::current->cullingMask->contains(Layer::UI))
//				continue;
//			Camera::current->Render();
//			if (Camera::current->framebuffer == nullptr)
//			{
//				Renderable::Draw(2, defaultRenderLayer);
//			}
//			else
//			{
//				Camera::current->framebuffer->Bind();
//				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//				Renderable::Draw(2, defaultRenderLayer);
//				Camera::current->framebuffer->Unbind();
//				glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
//				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			}
//		}
//
//		postProcessing->Process();
//
//		for (auto behaviour : Behaviour::behaviours)
//			behaviour.second->OnPostRender();
//
//		for (auto behaviour : Behaviour::behaviours)
//			behaviour.second->OnGUI();
//
//		// render 2d ui object.
//		Camera::current = uiCamera;
//		Camera::current->Render();
//		Renderable::Draw(1,uiRenderLayer);
//
//		FPS::CalculateFramePerSecond();
//		Input::setMouseWheel(0.0f);
//		Input::mouseDelta = Vector2::zero;
//
//		glFinish();
//		SwapBuffers(dc);
//	}
//	return  0;
//}


// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include "glew.h"    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif 

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib")

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "SpringEngine", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)& clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
