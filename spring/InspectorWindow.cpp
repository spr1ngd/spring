
#include "springeditor.h"
#include "inspectorwindow.h"
#include "selection.h"
#include "node.h"
#include "gameobject.h"

#include "transformeditor.h"
#include "lighteditor.h"
#include "materialeditor.h"
#include "particlerenderereditor.h"
#include "postprocesseditor.h"
#include "gameobjecteditor.h"

using namespace spring;
using namespace spring::editor;

std::map<const char*,InspectorEditor*> InspectorWindow::editors;

InspectorWindow::InspectorWindow(const char* name, bool openDefault) : EditorWindow(name,openDefault)
{
	windowFlags |= ImGuiWindowFlags_NoMove;

	AddInspectorEditor(new GameObjectEditor("GameObject","GameObject",true));
	AddInspectorEditor(new TransformEditor("Transform","Transform",true));
	AddInspectorEditor(new LightEditor("Light","Light",true));
	AddInspectorEditor(new MaterialEditor("MeshRenderer","MeshRenderer", true));
	AddInspectorEditor(new ParticleRendererEditor("ParticleRenderer","ParticleRenderer", true));
	AddInspectorEditor(new PostprocessEditor("PostProcessing", "PostProcessing", true));
}

void InspectorWindow::OnDrawWindow() 
{
	GameObject* selected = Selection::GetSelected();
	if (nullptr == selected)
		return;
	editors["GameObject"]->OnDrawInspector();
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Transform")) 
	{
		editors["Transform"]->OnDrawInspector();
		ImGui::TreePop();
	}
	for (auto node = selected->nodes.begin(); node != selected->nodes.end(); node++)
	{
		Node* nodePtr = *node;
		auto iterator = editors.find(nodePtr->GetTypeInfo().typeName);
		if (iterator == editors.end())
			continue;
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::TreeNode(iterator->second->editorName))
		{
			iterator->second->OnDrawInspector();
			ImGui::TreePop();
		}
	}
}