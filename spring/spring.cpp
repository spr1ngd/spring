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
	Screen::width = 1280 + 16;
	Screen::height = 720 + 39;

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

	// Initialize OpenGL loader
	bool err = glewInit() != GLEW_OK;
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// spring editor
	SpringEditor::Initialize();

	GUILayout::Initialize(window);

	//// Setup Dear ImGui context
	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	//// Setup Dear ImGui style
	//ImGui::StyleColorsLight();

	//// Setup Platform/Renderer bindings
	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init(glsl_version);

	glEnable(GL_MULTISAMPLE);
	// call the console window.
	AllocConsole(); 

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	bool bDrawSpringEngineToIMGUI = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		GUILayout::PreRender();

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

		// render scene window.
		GUILayout::Begin("Scene", &bDrawSpringEngineToIMGUI);
		ImGui::Image((ImTextureID)Camera::main->framebuffer->bufferId, ImVec2(800, 600), ImVec2(0, 1), ImVec2(1, 0));
		GUILayout::End();

		SpringEditor::DrawEditor();
		GUILayout::Render(window);
		glfwSwapBuffers(window);
	}

	SpringEditor::Release();
	AssetLoader::Release();
	for (auto behaviour : Behaviour::behaviours)
		behaviour.second->Destroy();

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
