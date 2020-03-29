#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DEBUG_NEW new
#endif
#include "GL/glew.h"
#include "GL/wglew.h"
#include <gl/GL.h>
#include "GLFW/glfw3.h"
#include "fileio.h"
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
#include "renderable.h"
#include "skybox.h"
#include "light.h"
#include "axishelper.h"
#include "cursor.h"
#include "input.h"
#include "physicsbasedrendering.h"
#include "scene.h"
#include "primitive.h"
#include "gameobject.h"

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
