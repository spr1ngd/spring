#include "menuwindow.h"
#include "scene.h"

using namespace spring;
using namespace spring::editor;

MenuWindow::MenuWindow(const char* name, bool defaultOpen) : EditorWindow(name,defaultOpen)
{
	this->windowFlags =
		// ImGuiWindowFlags_NoInputs |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoTitleBar| 
		ImGuiWindowFlags_MenuBar;
}

void MenuWindow::BeginWindow() 
{

}

void MenuWindow::EndWindow() 
{

}

void MenuWindow::OnDrawWindow() 
{
	bool open = true;
	ImGui::Begin("Menubar", &open, this->windowFlags);

	if (ImGui::BeginMenuBar()) 
	{
		if (ImGui::BeginMenu("Files")) 
		{
			if (ImGui::MenuItem("new scene", "CTRL+N", false)) 
			{

			}
			if (ImGui::MenuItem("load scene", "Ctrl+L", false))
			{

			}
			if (ImGui::MenuItem("save scene", "Ctrl+S", false))
			{
				Scene::SaveScene();
			}
			if (ImGui::MenuItem("quit spring", "Ctrl+Shift+Q", false))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Object")) 
		{
			if (ImGui::BeginMenu("Create", true))
			{
				if (ImGui::BeginMenu("3D", true))
				{
					if (ImGui::MenuItem("Cube", NULL, false, true)) 
					{

					}
					if (ImGui::MenuItem("Sphere", NULL, false, true))
					{

					}
					if (ImGui::MenuItem("Plane", NULL, false, true))
					{

					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	if (ImGui::Button("Play")) 
	{
		
	}

	ImGui::End();
}