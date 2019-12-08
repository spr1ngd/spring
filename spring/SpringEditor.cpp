#include "springeditor.h"

using namespace spring;
using namespace spring::editor;

bool SpringEditor::enabled = true;
InspectorWindow* SpringEditor::inspector = nullptr;
HierarchyWindow* SpringEditor::hierarchy = nullptr;

void SpringEditor::Initialize() 
{
	inspector = new InspectorWindow("Inspector", true);
	hierarchy = new HierarchyWindow("Hierarchy", true);
}

void SpringEditor::Release() 
{

}

void SpringEditor::DrawEditor() 
{
	EditorWindow::RenderWindows();
}