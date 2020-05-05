#include "editorapplication.h"
#include "input.h"
#include "picking.h"
#include "gizmos.h"

using namespace spring;
using namespace spring::editor;

void EditorApplication::Awake()
{

}

void EditorApplication::Update()
{ 
	if (Input::GetMouseDown(MOUSE_LEFT))
	{
		if (nullptr != Picking::selected && !Picking::selected->HasFlag(HideFlags_NotEditable))
		{
			Gizmos::DrawAxis(*Picking::selected->transform);
		}
	}

	if (Input::GetKeyDown(KeyCode::R)) 
	{
		Gizmos::SetAxisMode(AxisHelper::EditorGizmosMode::EditMode_Move);
	}
	if (Input::GetKeyDown(KeyCode::T)) 
	{
		Gizmos::SetAxisMode(AxisHelper::EditorGizmosMode::EditMode_Scale);
	}
	if (Input::GetKeyDown(KeyCode::Y))
	{
		Gizmos::SetAxisMode(AxisHelper::EditorGizmosMode::EditMode_Rotate);
	}
}

void EditorApplication::Destroy()
{

}