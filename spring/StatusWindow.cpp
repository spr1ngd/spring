#include "statuswindow.h"
#include "fps.h"

using namespace spring;
using namespace spring::editor;

StatusWindow::StatusWindow(const char* name, bool openDefault /* = false */) : EditorWindow(name,openDefault)
{
	this->windowFlags =
		ImGuiWindowFlags_NoResize|
		ImGuiWindowFlags_NoMove|
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoScrollbar;
}

void StatusWindow::OnDrawWindow() 
{
	ImGui::SetNextItemOpen(this->enabled, ImGuiCond_Once);

	ImGui::Text("FPS:%d",FPS::fps);
	ImGui::Text("Elapsed seconds per frame:%.2f",FPS::perFrameElapsed);
}