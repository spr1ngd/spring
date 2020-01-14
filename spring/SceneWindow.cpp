#include "scenewindow.h"
#include "springengine.h"
#include "imgui.h"
#include "postprocessing.h"

using namespace spring;
using namespace spring::editor;

SceneWindow::SceneWindow(const char* name, bool defaultOpen) :EditorWindow(name, defaultOpen)
{
	this->windowFlags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
}

void SceneWindow::OnDrawWindow() 
{
	if( nullptr == PostProcessing::postprocessing )
		ImGui::Image((ImTextureID) Camera::main->framebuffer->bufferId, ImVec2(Screen::width * 0.8f,Screen::height*0.8f), ImVec2(0, 1), ImVec2(1, 0));
	else 
		ImGui::Image((ImTextureID) PostProcessing::postprocessing->dstFramebuffer->buffer, ImVec2(Screen::width * 0.8f, Screen::height * 0.8f), ImVec2(0, 1), ImVec2(1, 0));
}