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
	Console::Log("orbit camera initialize...");
}

void OrbitCamera::Destroy() 
{
	Console::Log("orbit camera destroy...");
}

void OrbitCamera::Update() 
{   
	Vector3 direction = Vector3::zero;
	if (Input::GetKey(KeyCode::W)) 
		direction += Vector3::forward;
	if (Input::GetKey(KeyCode::S)) 
		direction += Vector3::back;
	if (Input::GetKey(KeyCode::A))
		direction += Vector3::left;
	if (Input::GetKey(KeyCode::D)) 
		direction += Vector3::right;
	this->moveDirection = Vector3::Normalize(direction);

	if (Input::GetMouseDown(MouseID::LEFT)) 
	{
	}
	if (Input::GetMouse(MouseID::LEFT)) 
	{
	}
	if (Input::GetMouseUp(MouseID::LEFT))
	{
	}

	this->Zoom();
	this->Rotate();
	this->Pan();
	this->Move();
} 

void OrbitCamera::Zoom()
{
	
}

void OrbitCamera::Rotate()
{
	if (!this->enableRotate)
		return;
	// Console::Log("Orbit camera rotate by mouse.");
}

void OrbitCamera::Pan()
{

}

void OrbitCamera::Move() 
{
	if (this->moveDirection == Vector3::zero)
		return;
	Console::Log("camera move.");
}