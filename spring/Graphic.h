#pragma once 
#include "skybox.h"
#include "camera.h"
#include "framebuffer.h"

namespace spring 
{
	class Graphic 
	{
	public:
		static glm::mat4 VIEW;
		static glm::mat4 PERSPECTIVE_PROJECTION;
		static glm::mat4 ORTHO_PROJECTION;
	};
}