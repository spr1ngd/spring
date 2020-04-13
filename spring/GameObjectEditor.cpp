#include "gameobjecteditor.h"

using namespace spring::editor;

void GameObjectEditor::OnDrawInspector() 
{
	GameObject* gameobject = Selection::GetSelected();
	if (nullptr == gameobject)
		return;

	ImGui::LabelText("name", gameobject->name);
	ImGui::Checkbox("visible", &gameobject->visible);
}