﻿
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
// todo : replaced input module by glfw interfaces.
// #include <windows.h>

#include "springengine.h"
// todo : integrate spring engine all .h file to springengine.h and clean up solution directory.
#include "springeditor.h"
#include "spring.h"
#include "sample.h"
#include "vector2.h"
#include "postprocessing.h"
#include "particlerenderer.h"
#include "shadercompiler.h"
#include "picking.h"
#include "console.h"

#include "gameapp.h"

using namespace spring;
using namespace spring::editor;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
	Screen::width = 1600;
	Screen::height = 900;

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

	PRINT_ERROR("this is spring engine,%s","hello world.");

	// spring editor
	SpringEditor::enabled = true;
	SpringEditor::Initialize();
	GUILayout::Initialize(window); // TODO: initialize content should be moved to spring editor.

	glEnable(GL_MULTISAMPLE);
	AllocConsole();

	// Our state
	bool show_demo_window = true;

	// TODO: try to load scene data
	// // create a scene or load a scene from scene data.
	// Scene* scene = new Scene();
	// Scene::current = scene;
	// 
	// // Game application entrance. this should be created by editor.
	// GameApp* gameApp = new GameApp();
	// gameApp->name = "GameApp";
	// gameApp->flags = NodeFlags::Static;

	Timer::Start();
	unsigned int* uiRenderLayer = new unsigned int[1]{ Layer::UI };
	unsigned int* defaultRenderLayer = new unsigned int[2]{ Layer::Default,Layer::Skybox };
	Camera* uiCamera = new Camera();
	uiCamera->name = "Internal UI Camera";
	uiCamera->cullingMask->set(uiRenderLayer);
	uiCamera->clearFlag = Camera::None;

	// TODO: serialize postprocessing setting to json
	// post processing
	PostProcessing::postprocessing = new class::PostProcessing();
	PostProcessing::postprocessing->enabled = true;
	// pp->bloom 
	PostProcessing::postprocessing->bloom->enable = true;
	PostProcessing::postprocessing->Initialize();

	if (PostProcessing::postprocessing->enabled == false)
	{
		FrameBuffer* mainFramebuffer = new FrameBuffer(Screen::width, Screen::height);
		mainFramebuffer->antiAliasing = AntiAliasingLevel::Level2;
		mainFramebuffer->depthbuffer = FrameBuffer::OnlyDepth;
		mainFramebuffer->Initialize();
		Camera::main->framebuffer = mainFramebuffer;

		FrameBuffer* renderTarget = new FrameBuffer(Screen::width, Screen::height);
		renderTarget->Initialize();
		Camera::main->renderTarget = renderTarget;
	}

	// standalone shader compiler (in a independent thread)
	ShaderCompiler shader_compiler;

	// gpu picking system
	Picking::enable = true;
	Picking::Initialize();

	// gizmos
	Gizmos::enable = true;

	Mathf::RandomSeed();
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		GUILayout::PreRender();

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window); 

		Timer::Time();
		Shader::shaderTimer = Vector4(Timer::totalTime,Mathf::Sin(Timer::totalTime),Mathf::Cos(Timer::totalTime),Mathf::Tan(Timer::totalTime));
		Gizmos::Render();

		// 将灯光阴影优先渲染
		Light::CastShadow();

		// camera view/projection matrix calculation must be earlier than update method ,otherwise camera's position maybe update late than other transform.
		for (vector<Camera*>::iterator cam = Camera::cameras.begin(); cam != Camera::cameras.end(); cam++)
			(*cam)->Update();

		for (auto behaviour : Behaviour::behaviours)
		{
			if (behaviour.second->enabled)
			{
				if (behaviour.second->awaked == false)
				{
					behaviour.second->Awake();
					behaviour.second->awaked = true;
				}
				behaviour.second->Update();
			}
		}
		ParticleRenderer::Update();

		for (auto behaviour : Behaviour::behaviours)
		{
			if (behaviour.second->enabled)
				behaviour.second->OnPreRender();
		}

		PostProcessing::postprocessing->Preprocess();

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
			}
		}

		// render for gpu picking system
		Picking::Render([&](void) 
			{
				Camera::current = Camera::main;
				Camera::current->Render();
				Renderable::Draw(2, defaultRenderLayer, [&](MeshRenderer* meshRenderer) 
					{
						Material* originMaterial = meshRenderer->material;
						meshRenderer->material = Picking::material;
						meshRenderer->material->shader->setColor("identify",Picking::Convert2Color(meshRenderer->GetRenderableId()));
						meshRenderer->Render();
						meshRenderer->material = originMaterial;
					});
			}); 

		PostProcessing::postprocessing->outline->Render(nullptr);
		PostProcessing::postprocessing->Process();

		for (auto behaviour : Behaviour::behaviours)
		{
			if(behaviour.second->enabled)
				behaviour.second->OnPostRender();
		}

		for (auto behaviour : Behaviour::behaviours)
		{
			if(behaviour.second->enabled)
				behaviour.second->OnGUI();
		}

		// render 2d ui object.
		Camera::current = uiCamera;
		Camera::current->Render();
		Renderable::Draw(1, uiRenderLayer);

		// FPS tool
		FPS::CalculateFramePerSecond();

		// Input system
		Input::setMouseWheel(0.0f);
		Input::mouseDelta = Vector2::zero; 

		// blit to render target
		if (PostProcessing::postprocessing->enabled == false) 
			Camera::main->framebuffer->Blit(*Camera::main->renderTarget);

		SpringEditor::DrawEditor();
		GUILayout::Render(window);

		glfwSwapBuffers(window);
		// _CrtDumpMemoryLeaks();
	}

	SpringEditor::Release();
	AssetLoader::Release();
	for (auto behaviour : Behaviour::behaviours)
	{
		if (behaviour.second->enabled)
			behaviour.second->Destroy();
	}

	// Cleanup remove those code to spring editor imgui...controller.
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
