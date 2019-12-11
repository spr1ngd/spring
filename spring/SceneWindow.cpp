#include "scenewindow.h"
#include "camera.h"
#include "imgui.h"

using namespace spring;
using namespace spring::editor;

SceneWindow::SceneWindow(const char* name, bool defaultOpen) :EditorWindow(name, defaultOpen)
{
	this->windowFlags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
}

void SceneWindow::OnDrawWindow() 
{
	ImGui::Image((ImTextureID) Camera::main->framebuffer->bufferId, ImVec2(800, 600), ImVec2(0, 1), ImVec2(1, 0));
}