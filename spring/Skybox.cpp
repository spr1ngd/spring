#include "skybox.h"
#include "console.h"
#include "camera.h"

using namespace spring;

void Skybox::Render() 
{
	if (this->material == nullptr)
	{
		// todo : how to throw exception in c plus plus ,and how to declare custom exception type.
		Console::Warning("can not render skybox without skybox material,please assign a sky box material.");
		return;
	}

	// skybox.transform.position changed with main camera.
	this->transform->position = Camera::main->transform->position;
	// when render skybox disable GL_DEPTH_TEST and GL_DEPTH_WRITE	
}