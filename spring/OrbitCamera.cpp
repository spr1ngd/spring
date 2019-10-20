#include "orbitcamera.h"
#include "console.h"
#include "input.h"
#include "mathf.h"

using namespace spring;
using namespace spring::editor;

Vector2 mouseOffset = Vector2::zero;

OrbitCamera::OrbitCamera() 
{
	this->camera = Camera::main;
}

void OrbitCamera::Awake() 
{

}

void OrbitCamera::Destroy() 
{

}

void OrbitCamera::Update() 
{   
	this->Zoom();
	if (Input::GetMouseDown(MouseID::LEFT)) 
	{
	}
	if (Input::GetMouse(MouseID::LEFT)) 
	{
		this->enableRotate = true;
	}
	if (Input::GetMouseUp(MouseID::LEFT))
	{
		this->enableRotate = false;
	}
	if (Input::GetMouse(MouseID::WHELL)) 
	{
		this->enablePan = true;
	}
	if (Input::GetMouseUp(MouseID::WHELL))
	{
		this->enablePan = false;
	}

	this->Zoom();
	this->Rotate();
	this->Pan();
} 

void OrbitCamera::Zoom()
{
	this->enableZoom = Input::mouseWheelDelta != 0.0f;
	this->distance = Vector3::Distance(this->target, this->camera->transform->GetPosition());
	if (!this->enableZoom)
		return;
	Vector3 direction = Vector3::Normalize(this->target - this->camera->transform->position) * Input::mouseWheelDelta;
	this->camera->transform->position += direction * zoomSpeed;
}

void OrbitCamera::Rotate()
{
	if (!this->enableRotate)
		return;

	float minY = -20.0f;
	float maxY = 80.0f; 

	float x = Input::mouseDelta.x / 10.0f * rotateSpeed;
	float y = Input::mouseDelta.y / 10.0f * rotateSpeed;

	y = Mathf::Clamp(y, minY, maxY);
	Quaternion rotation = Quaternion::Euler(y, x, 0.0f);

	Vector3 negativeDistance = Vector3(0.0f,0.0f,-this->distance);
	Vector3 position = rotation * negativeDistance + this->target;
	this->camera->transform->SetRotation(rotation);
	this->camera->transform->SetPosition(position);
}

void OrbitCamera::Pan()
{ 
	if (!this->enablePan)
		return;
	// todo : calculate transform.right after transform.eulerangle changed.
	// todo : what's the different between Quaternion and Euler angle.
}