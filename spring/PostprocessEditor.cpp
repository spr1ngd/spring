#include "postprocesseditor.h"

using namespace spring;
using namespace spring::editor;

PostprocessEditor::PostprocessEditor(const char*name,bool openDefault) : InspectorEditor(name,openDefault)
{
	
}

void PostprocessEditor::OnDrawInspector() 
{
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);

	// 

	// bloom setting
}