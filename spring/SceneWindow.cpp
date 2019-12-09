#include "scenewindow.h"
#include "camera.h"
#include "imgui.h"

using namespace spring;
using namespace spring::editor;

void SceneWindow::OnDrawWindow() 
{
	ImGui::Image((ImTextureID) Camera::main->framebuffer->bufferId, ImVec2(800, 600), ImVec2(0, 1), ImVec2(1, 0));
}