
#include <glm/glm.hpp>
#include "light.h"
#include "screen.h"

using namespace std;
using namespace spring;

map<const long, Light*> Light::lights;
Light* Light::main;

Light::Light()
{
	this->type = Light::Type::Directional;
	this->renderMode = Light::RenderMode::Pixel;
	this->color = Color::white;
	this->intensity = 1.0f;
	this->cullingMask = new LayerMask();
	this->shadowType = ShadowType::HardShadow;

	if (lights.size() == 0)
		Light::main = this;
	Light::lights.insert(pair<const long,Light*>(this->instanceId,this));
}

void Light::CastShadow() 
{
	if (this->shadowType == Light::NoShadow)
		return;
	if( this->shadow == nullptr )
		this->shadow = FrameBufferObject::GenDepthFramebuffer(Screen::width, Screen::height);

	// get view matrix
	// get projection matrix
}