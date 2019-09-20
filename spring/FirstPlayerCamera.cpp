#include "firstplayercamera.h"

using namespace spring;
using namespace spring::editor;

bool canMove = false; 

void FirstPlayerCamera::Awake() 
{
	this->camera = Camera::main;
	canMove = false;
}

void FirstPlayerCamera::Update() 
{
	if (this->camera == nullptr)
		return;
	Vector3 moveDirection;
	if (Input::GetKey(KeyCode::W)) moveDirection += Vector3::forward;
	if (Input::GetKey(KeyCode::S)) moveDirection += Vector3::back;
	if (Input::GetKey(KeyCode::A)) moveDirection += Vector3::left;
	if (Input::GetKey(KeyCode::D)) moveDirection += Vector3::right;
	if (Input::GetKey(KeyCode::Q)) moveDirection += Vector3::up;
	if (Input::GetKey(KeyCode::E)) moveDirection += Vector3::down;
	moveDirection = Vector3::Normalize(moveDirection);
	this->camera->transform->position += moveDirection * moveSpeed;
}