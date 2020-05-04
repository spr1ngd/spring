#include "gameobjecteditor.h"

using namespace spring::editor;

void GameObjectEditor::OnDrawInspector() 
{
	GameObject* gameobject = Selection::GetSelected();
	if (nullptr == gameobject)
		return;

	ImGui::LabelText("name", gameobject->name);

	bool visible = gameobject->GetActive();
	ImGui::Checkbox("visible", &visible);
	gameobject->SetActive(visible);
}