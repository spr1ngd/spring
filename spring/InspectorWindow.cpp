
#include "springeditor.h"
#include "selection.h"
#include "inspectorwindow.h"
#include "imgui.h"

using namespace spring;
using namespace spring::editor;

InspectorWindow::InspectorWindow(const char* name, bool openDefault) : EditorWindow(name,openDefault)
{
	this->windowFlags = ImGuiWindowFlags_NoMove;
}

void InspectorWindow::OnDrawWindow() 
{
	if (nullptr == Selection::node)
		return;
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Transform")) 
	{
		Transform* node = Selection::node->transform;

		float* position = new float[3]{ node->position.x,node->position.y,node->position.z };
		ImGui::DragFloat3("position", position);
		node->SetPosition(Vector3(position[0], position[1], position[2]));
		delete[] position;

		float* eulerangle = new float[3]{ node->eulerangle.x,node->eulerangle.y,node->eulerangle.z };
		ImGui::DragFloat3("eulerangle", eulerangle);
		node->SetEulerangle(Vector3(eulerangle[0], eulerangle[1], eulerangle[2]));
		delete[] eulerangle;

		float* scale = new float[3]{ node->scale.x,node->scale.y,node->scale.z };
		ImGui::DragFloat3("scale", scale);
		node->SetScale(Vector3(scale[0], scale[1], scale[2]));
		delete[] scale;

		ImGui::TreePop();
	}
}