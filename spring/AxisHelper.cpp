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
	if (nullptr != this->axisGizmos)
		this->axisGizmos->transform->SetLocalScale(Vector3(realRate, realRate, realRate));
	if (nullptr != this->scaleGizmos)
		this->scaleGizmos->transform->SetLocalScale(Vector3(realRate, realRate, realRate));
	if (nullptr != this->rotateGizmos)
		this->rotateGizmos->transform->SetLocalScale(Vector3(realRate, realRate, realRate));

	if (nullptr != Picking::selected )
	{ 
		if (this->currentEditAxis == AxisMode::None) 
		{

			if (strcmp(Picking::selected->name, "editor_gizmos_x") == 0)
			{
				this->currentEditAxis = AxisMode::X;
			}
			else if (strcmp(Picking::selected->name, "editor_gizmos_y") == 0)
			{
				this->currentEditAxis = AxisMode::Y;
			}
			else if (strcmp(Picking::selected->name, "editor_gizmos_z") == 0)
			{
				this->currentEditAxis = AxisMode::Z;
			}
			else
			{
				this->currentEditAxis = AxisMode::None;
			}
		}
	}

	if (this->currentEditAxis != AxisMode::None)
	{
		if (Input::GetMouseDown(MouseID::MOUSE_LEFT))
		{
			this->editing = true;
		}

		if (Input::GetMouse(MouseID::MOUSE_LEFT) && this->editing)
		{
			if (this->gizmosMode == AxisHelper::EditMode_Move)
			{
				Vector3 moveDir = Vector3::zero;
				if (this->currentEditAxis == AxisMode::X)
					moveDir = Vector3(1.0f, 0.0f, 0.0f) * Input::mouseDelta.x;
				else if (this->currentEditAxis == AxisMode::Y)
					moveDir = Vector3(0.0f, -1.0f, 0.0f) * Input::mouseDelta.y;
				else if (this->currentEditAxis == AxisMode::Z)
					moveDir = Vector3(0.0f, 0.0f, -1.0f) * Input::mouseDelta.x;

				if (nullptr != this->target)
				{
					Vector3 targetSrcPos = this->target->GetPosition();
					targetSrcPos += moveDir * this->moveSpeed;
					this->target->SetPosition(targetSrcPos);
				}
			}
			else if (this->gizmosMode == AxisHelper::EditMode_Scale) 
			{
				Vector3 scaleDir = Vector3::zero;
				if (this->currentEditAxis == AxisMode::X)
					scaleDir = Vector3(1.0f, 0.0f, 0.0f) * Input::mouseDelta.x;
				else if (this->currentEditAxis == AxisMode::Y)
					scaleDir = Vector3(0.0f, -1.0f, 0.0f) * Input::mouseDelta.y;
				else if (this->currentEditAxis == AxisMode::Z)
					scaleDir = Vector3(0.0f, 0.0f, -1.0f) * Input::mouseDelta.x;

				if (nullptr != this->target)
				{
					Vector3 targetSrcScale = this->target->GetLocalScale();
					targetSrcScale += scaleDir * this->scaleSpeed;
					this->target->SetLocalScale(targetSrcScale);
				}
			}
			else if (this->gizmosMode == AxisHelper::EditMode_Rotate) 
			{
				Vector3 rotateDir = Vector3::zero;
				if (this->currentEditAxis == AxisMode::X)
					rotateDir = Vector3(1.0f, 0.0f, 0.0f) * Input::mouseDelta.x;
				else if (this->currentEditAxis == AxisMode::Y)
					rotateDir = Vector3(0.0f, -1.0f, 0.0f) * Input::mouseDelta.y;
				else if (this->currentEditAxis == AxisMode::Z)
					rotateDir = Vector3(0.0f, 0.0f, -1.0f) * Input::mouseDelta.x;

				if (nullptr != this->target) 
				{
					Vector3 targetSrcEuler = this->target->GetEulerangle();
					targetSrcEuler += rotateDir * this->rotateSpeed;
					this->target->SetEulerangle(targetSrcEuler);
				}
			}
		}
	}

	if (Input::GetMouseUp(MouseID::MOUSE_LEFT))
	{
		this->editing = false;
		this->currentEditAxis = AxisMode::None;
	} 

	if (nullptr != Camera::main)
	{
		auto orbit = Camera::main->gameobject->GetNode<OrbitCamera>();
		if (nullptr != orbit)
			orbit->enabled = !this->editing;
	}

	if (nullptr != this->target)
	{
		if (nullptr != axisGizmos)
		{
			axisGizmos->transform->SetPosition(this->target->GetPosition());
			axisGizmos->transform->SetEulerangle(this->target->GetEulerangle());
		}
		if (nullptr != scaleGizmos)
		{
			scaleGizmos->transform->SetPosition(this->target->GetPosition());
			scaleGizmos->transform->SetEulerangle(this->target->GetEulerangle());
		}
		if (nullptr != rotateGizmos)
		{
			rotateGizmos->transform->SetPosition(this->target->GetPosition());
			rotateGizmos->transform->SetEulerangle(this->target->GetEulerangle());
		}
	}
}

void AxisHelper::Destroy() 
{

}