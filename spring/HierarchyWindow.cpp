#include "hierarchywindow.h"
#include "imgui.h"
#include "node.h"
#include "selection.h"
#include "scene.h"
#include "console.h"

using namespace spring;
using namespace spring::editor;

HierarchyWindow::HierarchyWindow(const char* name, bool openDefault) : EditorWindow(name, openDefault) 
{
	this->windowFlags = ImGuiWindowFlags_NoMove;
}

static int selection_mask = (1 << 0);

void DrawTree(int& clickedNode,int& clickedIndex, Node& node ,ImGuiTreeNodeFlags flags)
{
	for (auto item = node.children.begin(); item != node.children.end(); item++) 
	{
		clickedIndex++;
		Node* child = *item;
		ImGuiTreeNodeFlags node_flag = flags;
		const bool isSelected = (selection_mask & (1 << clickedIndex)) != 0; 
		if (isSelected)
		{
			node_flag |= ImGuiTreeNodeFlags_Selected;
			Selection::node = child;
		}
		if (ImGui::TreeNodeEx(child->name, node_flag))
		{
			if (ImGui::IsItemClicked())
				clickedNode = clickedIndex;
			ImGui::SameLine(0.0f);
			ImGui::Checkbox("", &child->visible);
			DrawTree(clickedNode,clickedIndex,*child,flags);
			ImGui::TreePop();
		}
	}
}

void HierarchyWindow::OnDrawWindow() 
{
	static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

	if (Scene::current == nullptr)
		return;

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("SceneName")) 
	{
		int clickedNode = -1;
		int clickedIndex = 0;
		
		for (int i = 0; i < (int)Scene::current->nodes.size(); i++)
		{
			Node* node = Scene::current->nodes[i];
			if (node->flags == NodeFlags::BuiltIn)
				continue;
			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool isSelected = (selection_mask & (1 << clickedIndex)) != 0; // 不能和id匹配，因为i无法递归到别的函数
			if (isSelected)
			{
				node_flags |= ImGuiTreeNodeFlags_Selected;
				Selection::node = node;
			}
			if (ImGui::TreeNodeEx(node->name, node_flags))
			{
				if (ImGui::IsItemClicked())
					clickedNode = clickedIndex;
				ImGui::SameLine(0.0f);
				ImGui::Checkbox("", &node->visible);
				DrawTree(clickedNode, clickedIndex, *node, base_flags);
				ImGui::TreePop();
			}
			clickedIndex++;
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