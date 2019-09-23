#include "orbitcamera.h"
#include "console.h"
#include "input.h"

using namespace spring;
using namespace spring::editor;
 

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
	if (!this->enableZoom)
		return;
	Vector3 direction = Vector3::Normalize(this->target - this->camera->transform->position) * Input::mouseWheelDelta;
	this->camera->transform->position += direction * zoomSpeed;
}

void OrbitCamera::Rotate()
{
	if (!this->enableRotate)
		return;
	Console::Log("Orbit camera rotate around center.");

	// 解决将向量旋转多少度的问题

	Vector3 offset = this->camera->transform->position - this->target;
	this->camera->transform->position -= offset;
	this->camera->transform->eulerangle.x += this->rotateSpeed;
	this->camera->transform->position += Vector3::Normalize(this->camera->transform->eulerangle) * Vector3::Magnitude(offset);
}

void OrbitCamera::Pan()
{ 
	if (!this->enablePan)
		return;
	// todo : calculate transform.right after transform.eulerangle changed.
	// todo : what's the different between Quaternion and Euler angle.
}