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
		if (nullptr != Picking::selected)
		{
			Gizmos::DrawAxis(*Picking::selected->transform);
		}
	}
}

void EditorApplication::Destroy()
{

}