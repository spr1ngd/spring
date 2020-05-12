#include "statuswindow.h"
#include "fps.h"
#include "graphicprofiler.h"

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
	ImGui::Text("Drawcall count : %d",GraphicProfiler::GetDrawcall());
	ImGui::Text("Triangle count : %d", GraphicProfiler::GetTriangles());
	ImGui::Text("Vertex count : %d", GraphicProfiler::GetVertices());
}