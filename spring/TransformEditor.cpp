#include "transformeditor.h"
#include "selection.h"

using namespace spring::editor;

void TransformEditor::OnDrawInspector() 
{
	Transform* node = Selection::GetSelected()->transform;

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
}