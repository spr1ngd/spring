#include "springeditor.h"
#include "particlerenderereditor.h"
#include "materialeditor.h"
#include "postprocesseditor.h"
#include "pickingeditor.h"

#include "editorgizmosutility.h"

using namespace spring;
using namespace spring::editor;

bool SpringEditor::enabled = true;
bool SpringEditor::maximize = false;
InspectorWindow* SpringEditor::inspector = nullptr;
HierarchyWindow* SpringEditor::hierarchy = nullptr;
SceneWindow* SpringEditor::scene = nullptr;
MenuWindow* SpringEditor::menu = nullptr;
StatusWindow* SpringEditor::status = nullptr;

void SpringEditor::Initialize() 
{
	if (enabled == false)
		return;
	scene = new SceneWindow("Scene",true);
	inspector = new InspectorWindow("Inspector", true);
	hierarchy = new HierarchyWindow("Hierarchy", true);
	menu = new MenuWindow("Menu",true);
	status = new StatusWindow("Status",false);

	EditorGizmosUtility::Initialize();
}

void SpringEditor::Release() 
{

}

void SpringEditor::DrawEditor() 
{
	if (enabled == false)
		return;
	EditorWindow::RenderWindows();
}