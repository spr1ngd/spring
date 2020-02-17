#include "inspectoreditor.h"

using namespace spring;
using namespace spring::editor;

InspectorEditor::InspectorEditor(const char* name,bool openDefault) : EditorWindow(name,openDefault)
{

}

void InspectorEditor::Show() 
{
	EditorWindow::Show();
}

void InspectorEditor::Hide() 
{
	EditorWindow::Hide();
}

void InspectorEditor::OnDrawWindow() 
{
	this->OnDrawInspector();
}

void InspectorEditor::OnDrawInspector()
{
	
}