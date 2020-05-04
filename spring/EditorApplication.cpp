#include "editorapplication.h"
#include "gameobject.h"
#include "primitive.h"
#include "meshrenderer.h"
#include "picking.h"
#include "console.h"

using namespace spring;
using namespace spring::editor;

void EditorApplication::Awake()
{
	axisGizmos = Primitive::CreateGizmo(Primitive::GizmoType::Move);
}

void EditorApplication::Update()
{ 
	// axis.
	auto renderers = axisGizmos->GetNodesInChildren<MeshRenderer>();
	for (auto renderer : renderers)
	{
		MeshRenderer* mr = renderer;
		mr->material->shader->setVec3("WorldSpaceAxisPos", axisGizmos->transform->position);
	}

	if (nullptr != Picking::selected) 
	{
		PRINT_LOG("select : %s",Picking::selected->name);
		if (Picking::selected == this->axisGizmos) 
		{
			PRINT_ERROR("select axis gizmos editor.");
		}
	}
}

void EditorApplication::Destroy()
{

}