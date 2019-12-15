#include "orbitcamera.h"
#include "console.h"
#include "input.h"
#include "mathf.h"

using namespace spring;
using namespace spring::editor;

Vector2 mouseOffset = Vector2::zero;
float x = 0.0f, y = 0.0f;

OrbitCamera::OrbitCamera() 
{
	this->camera = Camera::main;
}

void OrbitCamera::Awake() 
{
	auto euler = this->camera->transform->GetEulerangle();
	x = euler.x;
	y = euler.y;
	this->distance = Vector3::Distance(this->target, this->camera->transform->GetPosition());
}

void OrbitCamera::Destroy() 
{

}

void OrbitCamera::Update() 
{    
	if (Input::GetMouseDown(MouseID::MOUSE_LEFT)) 
	{

	}
	if (Input::GetMouse(MouseID::MOUSE_LEFT)) 
	{
		this->enableRotate = true;
	}
	if (Input::GetMouseUp(MouseID::MOUSE_LEFT))
	{
		this->enableRotate = false;
	}
	if (Input::GetMouse(MouseID::MOUSE_WHEEL)) 
	{
		this->enablePan = true;
	}
	if (Input::GetMouseUp(MouseID::MOUSE_WHEEL))
	{
		this->enablePan = false;
	}

	this->Zoom();
	this->Rotate();
	// this->Pan();
	this->camera->center = this->target;
} 

void OrbitCamera::Zoom()
{
	this->enableZoom = Input::mouseWheelDelta != 0.0f;
	if (!this->enableZoom)
		return;
	this->distance = Mathf::Clamp(this->distance - Input::mouseWheelDelta * zoomSpeed,this->minDistance,this->maxDistance);
	Vector3 direction = Vector3::Normalize(this->camera->transform->position - this->target);
	this->camera->transform->position = direction * this->distance;
}

void OrbitCamera::Rotate()
{
	if (!this->enableRotate)
		return;

	float minY = -80.0f;
	float maxY = 20.0f;

	x -= Input::mouseDelta.x / 10.0f * rotateSpeed;
	y += Input::mouseDelta.y / 10.0f * rotateSpeed;

	y = Mathf::Clamp(y, minY, maxY);
	Quaternion rotation = Quaternion::Euler(x, y, 0.0f);

	Vector3 negativeDistance = Vector3(0.0f,0.0f,this->distance);
	Vector3 position = rotation * negativeDistance + this->target;
	this->camera->transform->SetRotation(rotation);
	this->camera->transform->SetPosition(position);

}

void OrbitCamera::Pan()
{
	if (!this->enablePan)
		return;

	float deltaX = Input::mouseDelta.x / 10.0f * this->panSpeed;
	float deltaZ = Input::mouseDelta.y / 10.0f * this->panSpeed; 
	Vector3 offsetX = -this->camera->transform->right * deltaX;
	Vector3 offsetZ = this->camera->transform->forword * deltaZ;
	Vector3 offset = offsetX + offsetZ;
	Vector3 pos = offset + this->camera->transform->GetPosition();
	this->target = offset + this->target;
	this->camera->transform->SetPosition(pos);
}