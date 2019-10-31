#pragma once

#include "console.h"
#include "space.h"
#include "layer.h"
#include "timer.h"
#include "mathf.h"
#include "node.h"
#include "transform.h"
#include "gizmos.h"
#include "screen.h"
#include "environment.h"
#include "application.h"
#include "modelloader.h"
#include "shader.h"
#include "meshrenderer.h"
#include "mesh.h"
#include "material.h"
#include "camera.h"
#include "behaviour.h"
#include "vertex.h"
#include "input.h"
#include "renderable.h"
#include "skybox.h"
#include "light.h"
#include "axishelper.h"

// spring engine editor 
#include "orbitcamera.h"
#include "firstplayercamera.h"
#include "fps.h"

namespace spring
{
	class SpringEngine 
	{
	public:
		const char* VERSION = "V0.0.01";
	};
}
