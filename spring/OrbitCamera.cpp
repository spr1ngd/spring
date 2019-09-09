#include "orbitcamera.h"
#include "console.h"
#include "input.h"

using namespace spring;
using namespace spring::editor;

OrbitCamera::OrbitCamera() 
{

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
	if (Input::GetKey(KeyCode::W)) 
	{

	}
	if (Input::GetKey(KeyCode::S)) 
	{

	}
	if (Input::GetKey(KeyCode::A))
	{

	}
	if (Input::GetKey(KeyCode::D)) 
	{

	}

	if (Input::GetMouse(MouseID::LEFT)) 
	{
		this->enableRotate = true;
	}
	if (Input::GetMouse(MouseID::RIGHT)) 
	{

	}
	if (Input::GetMouse(MouseID::WHELL)) 
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

}

void OrbitCamera::Pan()
{

}

void OrbitCamera::Move() 
{

}