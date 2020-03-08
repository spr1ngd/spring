#include "statuswindow.h"

using namespace spring;
using namespace spring::editor;

StatusWindow::StatusWindow(const char* name, bool openDefault /* = false */) : EditorWindow(name,openDefault)
{
	this->windowFlags =
		ImGuiWindowFlags_NoResize|
		ImGuiWindowFlags_NoMove|
		ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoScrollbar;
}

void StatusWindow::OnDrawWindow() 
{
	ImGui::SetNextItemOpen(this->enabled, ImGuiCond_Once);

	ImGui::Text("FPS %d",60);
}