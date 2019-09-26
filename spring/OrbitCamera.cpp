#include "orbitcamera.h"
#include "console.h"
#include "input.h"

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
	if (!this->enableZoom)
		return;
	Vector3 direction = Vector3::Normalize(this->target - this->camera->transform->position) * Input::mouseWheelDelta;
	this->camera->transform->position += direction * zoomSpeed;
}

void OrbitCamera::Rotate()
{
	if (!this->enableRotate)
		return;
	Console::LogFormat("Orbit camera rotate around center.  offset (%f,%f)",Input::mouseDelta.x,Input::mouseDelta.y);

	// 
}

void OrbitCamera::Pan()
{ 
	if (!this->enablePan)
		return;
	// todo : calculate transform.right after transform.eulerangle changed.
	// todo : what's the different between Quaternion and Euler angle.
}