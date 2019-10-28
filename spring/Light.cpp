#include "light.h"
#include "console.h"

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
	Light::lights.insert(pair<const long,Light*>(this->instanceId,this));
}