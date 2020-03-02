#include "pickingeditor.h"
#include "picking.h"

using namespace spring;
using namespace spring::editor;

PickingEditor::PickingEditor(const char* windowName, bool openDefault /* = true */) : InspectorEditor(windowName,openDefault)
{

}

void PickingEditor::OnDrawInspector() 
{
	ImGui::SetNextItemOpen(true,ImGuiCond_Once);

	ImGui::Image((ImTextureID)Picking::colorbuffer->buffer,ImVec2(160,90),ImVec2(0,1),ImVec2(1,0));
}