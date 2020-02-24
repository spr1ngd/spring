#include "springeditor.h"
#include "particlerenderereditor.h"
#include "materialeditor.h"

using namespace spring;
using namespace spring::editor;

bool SpringEditor::enabled = true;
InspectorWindow* SpringEditor::inspector = nullptr;
HierarchyWindow* SpringEditor::hierarchy = nullptr;
SceneWindow* SpringEditor::scene = nullptr;

// inspector editor windows
ParticleRendererEditor* particleEditor = nullptr;
MaterialEditor* materialEditor = nullptr;

void SpringEditor::Initialize() 
{
	scene = new SceneWindow("Scene",true);
	inspector = new InspectorWindow("Inspector", true);
	hierarchy = new HierarchyWindow("Hierarchy", true);

	particleEditor = new ParticleRendererEditor("ParticleRenderer",true);
	materialEditor = new MaterialEditor("Mesh Renderer",true);
}

void SpringEditor::Release() 
{

}

void SpringEditor::DrawEditor() 
{
	EditorWindow::RenderWindows();
}