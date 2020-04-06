
#include "springeditor.h"
#include "selection.h"
#include "inspectorwindow.h"
#include "imgui.h"
#include "gameobject.h"

#include "transformeditor.h"
#include "lighteditor.h"
#include "materialeditor.h"
#include "postprocesseditor.h"
#include "gameobjecteditor.h"

using namespace spring;
using namespace spring::editor;

std::map<const char*,InspectorEditor*> InspectorWindow::editors;

InspectorWindow::InspectorWindow(const char* name, bool openDefault) : EditorWindow(name,openDefault)
{
	AddInspectorEditor(new GameObjectEditor("GameObject","GameObject",true));
	AddInspectorEditor(new TransformEditor("Transform","Transform",true));
	AddInspectorEditor(new LightEditor("Light","Light",true));
	AddInspectorEditor(new MaterialEditor("MeshRenderer","MeshRenderer", true));
	AddInspectorEditor(new MaterialEditor("ParticleRenderer","ParticleRenderer", true));
	AddInspectorEditor(new PostprocessEditor("PostProcessing", "PostProcessing", true));
}

void InspectorWindow::OnDrawWindow() 
{
	if (nullptr == Selection::gameobject)
		return;

	for (auto ie = editors.begin(); ie != editors.end(); ie++) 
	{
		InspectorEditor* inspectorEditor = ie->second;
		// TODO: determine whether draw this inspector editor, draw inspector types decided by selection::gameobject additional nodes
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode(inspectorEditor->editorName))
		{
			inspectorEditor->OnDrawInspector();
			ImGui::TreePop();
		}
	}
}