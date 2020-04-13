#include "editorgizmosutility.h"
#include "gizmos.h"
#include "selection.h"

using namespace spring;
using namespace spring::editor;

void EditorGizmosUtility::Initialize() 
{
	Selection::OnSelect(&EditorGizmosUtility::DrawAxis);
}

void EditorGizmosUtility::DrawAxis(GameObject& target) 
{
	Gizmos::DrawAxis(target.transform);
}