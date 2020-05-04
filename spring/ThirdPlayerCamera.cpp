#include "thirdplayercamera.h"
#include "camera.h"

using namespace spring;
using namespace spring::editor;

ThirdPlayerCamera::ThirdPlayerCamera() 
{

}

ThirdPlayerCamera::~ThirdPlayerCamera() 
{

}

void ThirdPlayerCamera::Awake() 
{
	this->camera = Camera::main;
	this->camera->transform->eulerangle = Vector3(30.0f,0.0f,0.0f);
}

void ThirdPlayerCamera::Update() 
{
	// 控制小球在草地上进行运动
	// 跟随target
	this->camera->center = this->camera->transform->position + this->camera->transform->forword * 1.0f;
	if (nullptr == target)
		return;
	this->camera->transform->position = target->transform->position + Vector3(0.0,0.25f,-0.375f);
}

void ThirdPlayerCamera::Destroy() 
{

}