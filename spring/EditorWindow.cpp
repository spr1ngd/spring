#include "editorwindow.h"
#include "guilayout.h"

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
	GUILayout::Begin(this->name, &this->enabled, 0);
}

void EditorWindow::OnDrawWindow() 
{

}

void EditorWindow::EndWindow() 
{
	GUILayout::End();
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
		window->BeginWindow();
		window->OnDrawWindow();
		window->EndWindow();
	}
}