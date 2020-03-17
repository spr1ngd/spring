#include "imgui.h"
#include "scenewindow.h"
#include "springengine.h"
#include "postprocessing.h"

using namespace spring;
using namespace spring::editor;

SceneWindow::SceneWindow(const char* name, bool defaultOpen) :EditorWindow(name, defaultOpen)
{
	this->windowFlags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
}

void SceneWindow::OnDrawWindow() 
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	if( nullptr != PostProcessing::postprocessing && PostProcessing::postprocessing->enabled )
		ImGui::Image((ImTextureID)PostProcessing::outputFramebuffer->GetBuffer(), ImVec2(Screen::width * 0.6f, Screen::height * 0.6f), ImVec2(0, 1), ImVec2(1, 0));
	else
		ImGui::Image((ImTextureID)Camera::main->renderTarget->GetBuffer(), ImVec2(Screen::width * 0.8f, Screen::height * 0.8f), ImVec2(0, 1), ImVec2(1, 0));
}