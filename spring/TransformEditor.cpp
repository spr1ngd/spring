#include "transformeditor.h"
#include "selection.h"

using namespace spring;
using namespace spring::editor;

void TransformEditor::OnDrawInspector() 
{
	Transform* node = Selection::GetSelected()->transform;
	const Vector3 worldSpacePos = node->GetPosition();
	const Vector3 localSpacePos = node->GetLocalPosition();
	const Vector3 localSpaceEulerangle = node->GetEulerangle();
	const Vector3 localSpaceScale = node->GetLocalScale();

	// float* localPosition = new float[3]{ localSpacePos.x,localSpacePos.y,localSpacePos.z };
	// ImGui::DragFloat3("local position", localPosition);
	// node->SetLocalPosition(Vector3(localPosition[0], localPosition[1], localPosition[2]));
	// delete[] localPosition;

	float* position = new float[3]{ worldSpacePos.x,worldSpacePos.y,worldSpacePos.z };
	ImGui::DragFloat3("position", position);
	node->SetPosition(Vector3(position[0], position[1], position[2]));
	delete[] position;

	float* localEulerangle = new float[3]{ localSpaceEulerangle.x,localSpaceEulerangle.y,localSpaceEulerangle.z };
	ImGui::DragFloat3("eulerangle", localEulerangle);
	node->SetEulerangle(Vector3(localEulerangle[0], localEulerangle[1], localEulerangle[2]));
	delete[] localEulerangle;

	float* localScale = new float[3]{ localSpaceScale.x,localSpaceScale.y,localSpaceScale.z };
	ImGui::DragFloat3("local scale", localScale);
	node->SetLocalScale(Vector3(localScale[0], localScale[1], localScale[2]));
	delete[] localScale;
}