#include "orbitcamera.h"
#include "console.h"

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

}
