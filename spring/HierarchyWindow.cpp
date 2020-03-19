#include "hierarchywindow.h"
#include "imgui.h"
#include "node.h"
#include "selection.h"
#include "scene.h"

using namespace spring;
using namespace spring::editor;

HierarchyWindow::HierarchyWindow(const char* name, bool openDefault) : EditorWindow(name, openDefault) 
{
	// this->windowFlags = ImGuiWindowFlags_NoMove;
}

void HierarchyWindow::OnDrawWindow() 
{
	static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("SceneName")) 
	{
		static int selection_mask = (1 << 2);
		int clickedNode = -1;
		
		for (int i = 0; i < (int)Scene::current->nodes.size(); i++)
		{
			if (i == 0)
				ImGui::SetNextItemOpen(true,ImGuiCond_Once);
			Node* node = Scene::current->nodes[i];
			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool isSelected = (selection_mask & (1 << i)) != 0;
			if (isSelected)
			{
				node_flags |= ImGuiTreeNodeFlags_Selected;
				Selection::node = node;
			}
			if (nullptr != node->name)
			{
				if (ImGui::TreeNodeEx(node->name, node_flags))
				{
					if (ImGui::IsItemClicked())
						clickedNode = i;
					// 递归绘制所有node 但默认不展开
					ImGui::TreePop();
				}
			}
		}
		if (clickedNode != -1) 
		{
			if (ImGui::GetIO().KeyCtrl) // multi selection
			{
				selection_mask ^= (1 << clickedNode);
			}
			else 
			{
				selection_mask = (1 << clickedNode);
			}
		}
		ImGui::TreePop();
	}
}