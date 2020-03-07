#include "springeditor.h"
#include "particlerenderereditor.h"
#include "materialeditor.h"
#include "postprocesseditor.h"
#include "pickingeditor.h"

using namespace spring;
using namespace spring::editor;

bool SpringEditor::enabled = true;
InspectorWindow* SpringEditor::inspector = nullptr;
HierarchyWindow* SpringEditor::hierarchy = nullptr;
SceneWindow* SpringEditor::scene = nullptr;
MenuWindow* SpringEditor::menu = nullptr;

// inspector editor windows
ParticleRendererEditor* particleEditor = nullptr;
MaterialEditor* materialEditor = nullptr;
PostprocessEditor* postprocessEditor = nullptr;
PickingEditor* pickingEditor = nullptr;

void SpringEditor::Initialize() 
{
	scene = new SceneWindow("Scene",true);
	inspector = new InspectorWindow("Inspector", true);
	hierarchy = new HierarchyWindow("Hierarchy", true);
	menu = new MenuWindow("Menu",true);

	particleEditor = new ParticleRendererEditor("ParticleRenderer",true);
	materialEditor = new MaterialEditor("Mesh Renderer",true);
	postprocessEditor = new PostprocessEditor("PostProcessing",true);
	pickingEditor = new PickingEditor("Picking System",true);
}

void SpringEditor::Release() 
{

}

void SpringEditor::DrawEditor() 
{
	EditorWindow::RenderWindows();
}