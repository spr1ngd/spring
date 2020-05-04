#include "springengine.h"
#include "axishelper.h"
#include "gizmos.h"
#include "picking.h"
#include "orbitcamera.h"

using namespace spring;
using namespace spring::editor;

AxisHelper::AxisHelper() : target(nullptr), axisGizmos(nullptr), rotateGizmos(nullptr), scaleGizmos(nullptr) 
{

}

void AxisHelper::SetTarget(Transform* target)
{
	this->target = target;
}
void AxisHelper::SetAxisMode(AxisHelper::EditorGizmosMode mode)
{
	this->gizmosMode = mode;
	axisGizmos->SetActive(this->gizmosMode == AxisHelper::EditMode_Move);
	scaleGizmos->SetActive(this->gizmosMode == AxisHelper::EditMode_Scale);
	rotateGizmos->SetActive(gizmosMode == AxisHelper::EditMode_Rotate);
}

void AxisHelper::Awake() 
{
	axisGizmos = Primitive::CreateGizmo(Primitive::GizmoType::Move);
	scaleGizmos = Primitive::CreateGizmo(Primitive::GizmoType::Scale);
	rotateGizmos = Primitive::CreateGizmo(Primitive::GizmoType::Rotate);
	axisGizmos->SetActive(this->gizmosMode == AxisHelper::EditMode_Move);
	scaleGizmos->SetActive(this->gizmosMode == AxisHelper::EditMode_Scale);
	rotateGizmos->SetActive(gizmosMode == AxisHelper::EditMode_Rotate);
}

void AxisHelper::Update() 
{ 
	float distance = Vector3::Distance(this->transform->GetPosition(), Camera::main->transform->GetPosition());
	float realRate = distance / 5.0f;
	if( nullptr != this->axisGizmos )
		this->axisGizmos->transform->SetScale(Vector3(realRate, realRate, realRate));
	if( nullptr != this->scaleGizmos)
		this->scaleGizmos->transform->SetScale(Vector3(realRate, realRate, realRate));

	if (nullptr != Picking::selected && this->currentEditAxis == AxisMode::None)
	{
		if (strcmp(Picking::selected->name, "editor_gizmos_x_axis") == 0)
		{
			this->currentEditAxis = AxisMode::X;
		}
		else if (strcmp(Picking::selected->name, "editor_gizmos_y_axis") == 0)
		{
			this->currentEditAxis = AxisMode::Y;
		}
		else if (strcmp(Picking::selected->name, "editor_gizmos_z_axis") == 0)
		{
			this->currentEditAxis = AxisMode::Z;
		}
		else
		{
			this->currentEditAxis = AxisMode::None;
		}
	}

	if (nullptr != Camera::main)
	{
		auto orbit = Camera::main->gameobject->GetNode<OrbitCamera>();
		if (nullptr != orbit)
			orbit->enabled = !this->editing;
	}

	if (this->currentEditAxis != AxisMode::None)
	{
		if (Input::GetMouse(MouseID::MOUSE_LEFT))
		{
			this->editing = true;
			if (this->currentEditAxis == AxisMode::X)
				this->moveDir = Vector3(1.0f, 0.0f, 0.0f) * Input::mouseDelta.x;
			else if (this->currentEditAxis == AxisMode::Y)
				this->moveDir = Vector3(0.0f, -1.0f, 0.0f) * Input::mouseDelta.y;
			else if (this->currentEditAxis == AxisMode::Z)
				this->moveDir = Vector3(0.0f, 0.0f, -1.0f) * Input::mouseDelta.x;

			if (nullptr != this->target) 
			{
				Vector3 targetSrcPos = this->target->GetPosition();
				targetSrcPos += this->moveDir * moveSpeed;
				this->target->SetPosition(targetSrcPos);
			}
		}
	}

	if (Input::GetMouseUp(MouseID::MOUSE_LEFT))
	{
		this->editing = false;
		this->currentEditAxis = AxisMode::None;
	}

	if (nullptr != this->target)
	{
		if( nullptr != axisGizmos )
			axisGizmos->transform->SetPosition(this->target->GetPosition());
		if( nullptr != scaleGizmos )
			scaleGizmos->transform->SetPosition(this->target->GetPosition());
	}
}

void AxisHelper::Destroy() 
{

}