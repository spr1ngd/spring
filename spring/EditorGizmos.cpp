#include "editorapplication.h"
#include "gameobject.h"
#include "primitive.h"
#include "meshrenderer.h"

using namespace spring;
using namespace spring::editor;

void EditorGizmos::Awake() 
{
	axisGizmos = Primitive::CreateGizmo(Primitive::GizmoType::Move);
}

void EditorGizmos::Update() 
{ 
	// axis.
	auto renderers = axisGizmos->GetNodesInChildren<MeshRenderer>();
	for (auto renderer : renderers)
	{
		MeshRenderer* mr = renderer;
		mr->material->shader->setVec3("WorldSpaceAxisPos", axisGizmos->transform->position);
	}
}

void EditorGizmos::Destroy() 
{

}