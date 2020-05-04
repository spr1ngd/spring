#include "hierarchywindow.h"
#include "imgui.h"
#include "node.h"
#include "gameobject.h"
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

void DrawTree(int& clickedNode,int& clickedIndex, GameObject& parent ,ImGuiTreeNodeFlags flags)
{
	for (auto go = parent.children.begin(); go != parent.children.end(); go++)
	{
		GameObject* goPtr = *go;
		if ((goPtr->flags & HideFlags::HideFlags_HideInHierarchyWindow) == HideFlags::HideFlags_HideInHierarchyWindow)
			continue;
		clickedIndex++;
		ImGuiTreeNodeFlags node_flag = flags;
		const bool isSelected = (selection_mask & (1 << clickedIndex)) != 0; 
		if (isSelected)
		{
			node_flag |= ImGuiTreeNodeFlags_Selected;
			// Selection::gameobject = goPtr;
			Selection::Select(goPtr);
		}
		if (ImGui::TreeNodeEx(goPtr->name, node_flag))
		{
			if (ImGui::IsItemClicked())
				clickedNode = clickedIndex;
			DrawTree(clickedNode,clickedIndex,*goPtr,flags);
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
	if (ImGui::TreeNode(Scene::current->name)) 
	{
		int clickedNode = -1;
		int clickedIndex = 0;
		
		for (int i = 0; i < (int)Scene::current->gameobjects.size(); i++)
		{
			GameObject* gameobject = Scene::current->gameobjects[i];
			if ((gameobject->flags & HideFlags::HideFlags_HideInHierarchyWindow) == HideFlags::HideFlags_HideInHierarchyWindow)
				continue;
			ImGuiTreeNodeFlags node_flags = base_flags;
			const bool isSelected = (selection_mask & (1 << clickedIndex)) != 0;
			if (isSelected)
			{
				node_flags |= ImGuiTreeNodeFlags_Selected;
				// Selection::gameobject = gameobject;
				Selection::Select(gameobject);
			}
			if (ImGui::TreeNodeEx(gameobject->name, node_flags))
			{
				if (ImGui::IsItemClicked())
					clickedNode = clickedIndex;
				DrawTree(clickedNode, clickedIndex, *gameobject, base_flags);
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