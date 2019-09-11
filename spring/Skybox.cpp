#include "skybox.h"
#include "console.h"

using namespace spring;

void Skybox::Render() 
{
	if (this->material == nullptr)
	{
		// todo : how to throw exception in c plus plus ,and how to declare custom exception type.
		Console::Error("can not render skybox without skybox material,please assign a sky box material.");
		return;
	}

	// skybox.transform.position changed with main camera.
	// when render skybox disable GL_DEPTH_TEST and GL_DEPTH_WRITE	
}