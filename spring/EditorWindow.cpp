#include "editorwindow.h"
#include "guilayout.h"
#include <typeinfo>
#include "scenewindow.h"
#include "springeditor.h"

using namespace spring;
using namespace spring::editor;

std::vector<EditorWindow*> EditorWindow::editorWindows;

EditorWindow::EditorWindow(const char* name, bool openDefault )
{
	this->name = name;
	this->enabled = openDefault;
	editorWindows.push_back(this);
}

void EditorWindow::BeginWindow() 
{
	ImGui::Begin(this->name, &this->enabled, this->windowFlags);
}

void EditorWindow::OnDrawWindow() 
{

}

void EditorWindow::EndWindow() 
{
	ImGui::End();
}

void EditorWindow::Show() 
{
	this->enabled = true;
}

void EditorWindow::Hide()
{
	this->enabled = false;
}

EditorWindow* EditorWindow::OpenWindow(const char* name, bool openDefault) 
{
	EditorWindow* window = new EditorWindow(name, openDefault);
	return window;
}

void EditorWindow::CloseWindow(const char* name)
{
	for (auto item = editorWindows.begin(); item != editorWindows.end(); item++)
	{
		if ((*item)->name == name)
		{
			EditorWindow::editorWindows.erase(item);
			break;
		}
	}
}

void EditorWindow::CloseWindow(EditorWindow* window)
{
	if (nullptr == window)
		return;
	for (auto item = editorWindows.begin(); item != editorWindows.end(); item++) 
	{
		if (*item == window)
		{
			EditorWindow::editorWindows.erase(item);
			break;
		}
	}
}

void EditorWindow::RenderWindows() 
{
	for (auto item = editorWindows.begin(); item != editorWindows.end(); item++) 
	{
		EditorWindow* window = *item;
		if(SpringEditor::maximize && window->name != "Scene")
			continue;
		window->BeginWindow();
		window->OnDrawWindow();
		window->EndWindow();
	}
}