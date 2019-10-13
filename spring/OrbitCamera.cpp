#include "orbitcamera.h"
#include "console.h"
#include "input.h"
#include "matrix4x4.h"

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
	Vector3 distance = this->camera->transform->position - this->target;
	Matrix4x4 T = Matrix4x4::Translate(-distance.x, -distance.y, -distance.z);
	Matrix4x4 RY = Matrix4x4::RotateY(Input::mouseDelta.x / 10.0f * rotateSpeed);
	Vector3 axis = this->camera->transform->getRight();
	// Console::LogFormat("rotate axis %f,%f,%f", axis.x, axis.y, axis.z);
	// Console::ErrorFormat("camera pos %f,%f,%f", this->camera->transform->position.x, this->camera->transform->position.y, this->camera->transform->position.z);
	Matrix4x4 RR = Matrix4x4::Rotate(Input::mouseDelta.y / 10.0f * rotateSpeed, axis);
	Matrix4x4 IT = Matrix4x4::Translate(distance.x, distance.y, distance.z);

	this->camera->transform->position = IT * RY /** RR */* T * this->camera->transform->position;
	// this->camera->transform->LookAt(Vector3::zero);
}

void OrbitCamera::Pan()
{ 
	if (!this->enablePan)
		return;
	// todo : calculate transform.right after transform.eulerangle changed.
	// todo : what's the different between Quaternion and Euler angle.
}