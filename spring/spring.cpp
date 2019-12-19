#define _CRT_SECURE_NO_WARNINGS 

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
// todo : replaced input module by glfw interfaces.
// #include <windows.h>
#include "glew.h"
#include "wglew.h"
#include <gl/GL.h>
#include "GLFW/glfw3.h"
// todo : integrate spring engine all .h file to springengine.h and clean up solution directory.
#include "springeditor.h"
#include "springengine.h"
#include "spring.h"
#include "sample.h"
#include "vector2.h"
#include "postprocessing.h"

#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glew32.lib")
#pragma comment (lib,"opengl32.lib") 

using namespace spring;
using namespace spring::editor;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
	Screen::width = 1280;
	Screen::height = 720;

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

	// todo : add small icon for window
	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(Screen::width, Screen::height, "spring engine", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

	// glfw input callback 
	Input::InitializeInput(window);

	// init window cursor display mode.
	Cursor::InitializeCursor(window);
	Cursor::SetCursotMode(Cursor::Cursor_Normal);

	// Initialize OpenGL loader
	bool err = glewInit() != GLEW_OK;
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// spring editor
	SpringEditor::Initialize();
	GUILayout::Initialize(window); // TODO: initialize content should be moved to spring editor.

	glEnable(GL_MULTISAMPLE);
	AllocConsole(); 

	// Our state
	bool show_demo_window = true;

	// draw sample scene
	Sample* sample = new Sample();

	Timer::Start();
	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Awake();

	unsigned int* uiRenderLayer = new unsigned int[1]{ Layer::UI };
	unsigned int* defaultRenderLayer = new unsigned int[2]{ Layer::Default,Layer::Skybox };

	Camera* uiCamera = new Camera();
	uiCamera->name = "Internal UI Camera";
	uiCamera->cullingMask->set(uiRenderLayer);
	uiCamera->clearFlag = Camera::None;

	// 0. construct post processing instance.
	class::PostProcessing* postProcessing = new class::PostProcessing();
	postProcessing->enabled = false;
	postProcessing->antiAliasing->enabled = false;
	postProcessing->bloom->enabled = false;
	postProcessing->PreProcess();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		GUILayout::PreRender();

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window); 

		Timer::Time();
		Gizmos::Render();

		// 将灯光阴影优先渲染
		Light::CastShadow();

		// camera view/projection matrix calculation must be earlier than update method ,otherwise camera's position maybe update late than other transform.
		for (vector<Camera*>::iterator cam = Camera::cameras.begin(); cam != Camera::cameras.end(); cam++)
			(*cam)->Update();

		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->Update();

		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->OnPreRender();

		// draw 3d scene.
		for (vector<Camera*>::iterator cam = Camera::cameras.begin(); cam != Camera::cameras.end(); cam++)
		{
			Camera::current = *cam;
			if (Camera::current->cullingMask->contains(Layer::UI))
				continue;
			Camera::current->Render();
			if (Camera::current->framebuffer == nullptr)
			{
				Renderable::Draw(2, defaultRenderLayer);
			}
			else
			{
				Camera::current->framebuffer->Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				Renderable::Draw(2, defaultRenderLayer);
				Camera::current->framebuffer->Unbind();
				glClearColor(0.1f, 0.4f, 0.7f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
		}

		postProcessing->Process();

		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->OnPostRender();

		for (auto behaviour : Behaviour::behaviours)
			behaviour.second->OnGUI();

		// render 2d ui object.
		Camera::current = uiCamera;
		Camera::current->Render();
		Renderable::Draw(1, uiRenderLayer);

		// FPS tool
		FPS::CalculateFramePerSecond();

		// Input system
		Input::setMouseWheel(0.0f);
		Input::mouseDelta = Vector2::zero; 

		SpringEditor::DrawEditor();
		GUILayout::Render(window);

		glfwSwapBuffers(window);
	}

	SpringEditor::Release();
	AssetLoader::Release();
	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Destroy();

	// Cleanup remove those code to spring editor imgui...controller.
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
