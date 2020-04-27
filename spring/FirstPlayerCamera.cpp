#include "firstplayercamera.h"
#include "input.h"

using namespace spring;
using namespace spring::editor;

bool canMove = false; 

FirstPlayerCamera::FirstPlayerCamera() : camera(nullptr)
{

}

void FirstPlayerCamera::Awake() 
{
	this->camera = Camera::main;
	canMove = false;
	this->moveSpeed = 0.25f;
	this->rotateSpeed = 0.2f;


	this->transform->position = Vector3(-0.0, 0.0f, 0.0f);
	this->transform->eulerangle = Vector3(0.0f, 0.0f, 0.0f);
}

void FirstPlayerCamera::Update() 
{
	if (this->camera == nullptr)
		return;
	Vector3 moveDirection;
	if (Input::GetKey(KeyCode::W)) moveDirection += this->transform->forword;
	if (Input::GetKey(KeyCode::S)) moveDirection += -this->transform->forword;
	if (Input::GetKey(KeyCode::A)) moveDirection += this->transform->right;
	if (Input::GetKey(KeyCode::D)) moveDirection += -this->transform->right;
	if (Input::GetKey(KeyCode::Q)) moveDirection += -this->transform->up;
	if (Input::GetKey(KeyCode::E)) moveDirection += this->transform->up;
	moveDirection = Vector3::Normalize(moveDirection);
	this->camera->transform->position += moveDirection * moveSpeed;

	if (Input::GetMouse(MOUSE_RIGHT)) 
	{
		float xDelta = Input::mouseDelta.x;
		float yDelta = Input::mouseDelta.y;
		this->transform->eulerangle += Vector3(yDelta,-xDelta,0.0f) * rotateSpeed;
	}

	this->camera->center = this->camera->transform->position + this->camera->transform->forword * 1.0f;
}