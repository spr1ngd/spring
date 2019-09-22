#include "orbitcamera.h"
#include "console.h"
#include "input.h"

using namespace spring;
using namespace spring::editor;

Vector2 lastFrameMousePosition = Vector2::zero;

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

	}
	if (Input::GetMouseUp(MouseID::LEFT))
	{

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
	if (this->enableZoom)
	{
		// todo : fixed camera's center
		Vector3 zoomDirection = Vector3::Normalize(this->target - this->camera->transform->position) * Input::mouseWheelDelta;
		Vector3 zoomOffset = zoomDirection * zoomSpeed;
		this->camera->transform->position += zoomOffset;
	}
}

void OrbitCamera::Rotate()
{
	if (!this->enableRotate)
		return;
	// Console::Log("Orbit camera rotate by mouse.");
}

void OrbitCamera::Pan()
{ 
	if (!this->enablePan)
		return;
	Console::Log("mouse pan event");
	Vector2 offset = Input::mousePosition - lastFrameMousePosition;
	lastFrameMousePosition = Input::mousePosition;
	// translate along camera.transform.up
	// translate along camera.transform.right
}