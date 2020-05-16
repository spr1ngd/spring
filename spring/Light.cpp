
#include "glm/glm.hpp"
#include "light.h"
#include "screen.h"
#include "camera.h"
#include "meshrenderer.h"
#include "instancedrenderer.h"
#include "graphic.h"
#include "shader.h"
#include "misc.h"

using namespace std;
using namespace spring;

vector< Light*> Light::lights;
Light* Light::main;
Material* Light::depthMaterial;
Material* Light::tMaterial;
Material* instanceDepthMaterial;

Light::Light()
{
	this->lightId = lights.size();

	this->type = Light::Type::Directional;
	this->renderMode = Light::RenderMode::Pixel;
	this->color = Color::white;
	this->shadowType = ShadowType::HardShadow;

	// set the first light as scene main light source
	if (lights.size() == 0)
		Light::main = this;

	if (nullptr == depthMaterial)
	{
		// depthMaterial = new Material(Shader::Load("shadow/shadow.vs", "shadow/shadow.fs"));
		depthMaterial = new Material(Shader::Load("shadow/shadow(newer).vs", "shadow/shadow.fs"));
		instanceDepthMaterial = new Material(Shader::Load("shadow/shadow(instance).vs", "shadow/shadow.fs"));

		tMaterial = new Material(Shader::Load("fullscreen/fullscreen.vs", "shadow/shadow(display).fs"));
	}
	Light::lights.push_back(this);
}
Light::~Light()
{

}

void Light::ResetShaderLightParams() 
{
	Shader::ForEach([&](Shader* shader)
		{
			if (!shader->enableLighting)
				return;
			if (this->type == Light::Type::Directional)
				this->SetDirectionalLightParams(shader);
			else if (this->type == Light::Type::Spot)
				this->SetSpotLightParams(shader);
			else if (this->type == Light::Type::Point)
				this->SetPointLightParams(shader);
			else if (this->type == Light::Type::Area)
				this->SetAreaLightParams(shader);
			else
				return;
		});
}

void Light::SetDirectionalLightParams(Shader* shader)
{
	string arrayName = "dirLights";
	const char* intensityName = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_INTENSITY));
	const char* positionName = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_POSITION));
	const char* colorName = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_COLOR));
	shader->setVec3(positionName, this->transform->position);
	shader->setColor(colorName, this->color);
	shader->setFloat(intensityName, this->setting.intensity);
	delete[] intensityName;
	delete[] positionName;
	delete[] colorName;
}
void Light::SetSpotLightParams(Shader* shader) 
{
	string arrayName = "spotLights";
	char* intensityStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_INTENSITY);
	char* positionStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_POSITION);
	char* directionStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_DIRECTION);
	char* colorStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_COLOR);
	char* rangeStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_RANGE);
	char* constantStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_CONSTANT);
	char* linearStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_LINEAR);
	char* quadraticStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_QUADRATIC);
	char* cutoffStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_CUTOFF);
	char* outerCutoffStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_OUTERCUTOFF);
	shader->setVec3(positionStr, this->transform->position);
	shader->setColor(colorStr, this->color);
	shader->setVec3(directionStr, this->transform->GetEulerangle());
	shader->setFloat(intensityStr, this->setting.intensity);
	shader->setFloat(rangeStr, this->setting.range);
	shader->setFloat(constantStr, this->setting.constant);
	shader->setFloat(linearStr, this->setting.linear);
	shader->setFloat(quadraticStr, this->setting.quadratic);
	shader->setFloat(cutoffStr, glm::cos(glm::radians(this->setting.spotAngle / 2.0f)));
	shader->setFloat(outerCutoffStr, glm::cos(glm::radians(this->setting.outterAngle / 2.0f)));
	delete[] intensityStr;
	delete[] positionStr;
	delete[] directionStr;
	delete[] colorStr;
	delete[] rangeStr;
	delete[] constantStr;
	delete[] linearStr;
	delete[] quadraticStr;
	delete[] cutoffStr;
	delete[] outerCutoffStr;
}
void Light::SetPointLightParams(Shader* shader) 
{
	string arrayName = "pointLights";
	char* intensityStr = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_INTENSITY));
	char* positionStr = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_POSITION));
	char* colorStr = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_COLOR));
	char* rangeStr = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_RANGE));
	char* constantStr = spring::misc::string2c((arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_CONSTANT));
	char* linearStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_LINEAR);
	char* quadraticStr = spring::misc::string2c(arrayName + '[' + to_string(this->lightId) + "]." + _LIGHT_QUADRATIC);
	shader->setVec3(positionStr, this->transform->position);
	shader->setColor(colorStr, this->color);
	shader->setFloat(intensityStr, this->setting.intensity);
	shader->setFloat(rangeStr, this->setting.range);
	shader->setFloat(constantStr, this->setting.constant);
	shader->setFloat(linearStr, this->setting.linear);
	shader->setFloat(quadraticStr, this->setting.quadratic);
	delete[] intensityStr;
	delete[] positionStr;
	delete[] colorStr;
	delete[] rangeStr;
	delete[] constantStr;
	delete[] linearStr;
	delete[] quadraticStr;
}
void Light::SetAreaLightParams(Shader* shader) 
{

}

void Light::CastShadow() 
{ 
	// depth->CullFaceFunc(true, GL_FRONT);
	for (Light* light : Light::lights)
	{
		glViewport(0, 0, light->shadowMapping.shadowMapSize, light->shadowMapping.shadowMapSize);
		if (light->shadowType == Light::NoShadow)
			continue;
		if (light->shadow == nullptr)
		{
			// light->shadow = FrameBuffer::GenDepthFramebuffer(Screen::width, Screen::height);
			light->shadow = new FrameBuffer(light->shadowMapping.shadowMapSize, light->shadowMapping.shadowMapSize);
			light->shadow->colorFormat = ColorFormat::Shadow;
			light->shadow->Initialize();

			light->tbuffer = new FrameBuffer(light->shadowMapping.shadowMapSize, light->shadowMapping.shadowMapSize);
			light->tbuffer->colorFormat = ColorFormat::RGB24;
			light->tbuffer->Initialize();
		}

		glm::mat4 view = glm::lookAt(
			glm::vec3(light->transform->position.x,light->transform->position.y,light->transform->position.z),
			glm::vec3(0.0f,0.0f,0.0f),
			glm::vec3(0.0f,1.0f,0.0));
		light->lightSpaceMatrix = light->shadowMapping.projection * view;

		light->shadow->Bind();
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Renderable::Draw(light->layers.layers, [&](MeshRenderer* renderer)
			{
				if (renderer->material->castShadow)
				{
					Material* srcMaterial = renderer->material;
					if( renderer->enableGPUInstance ) 
						renderer->material = instanceDepthMaterial;
					else
						renderer->material = depthMaterial;
					// todo : make camera culling mask equal with light.
					renderer->Render(view,light->shadowMapping.projection);
					renderer->material = srcMaterial;
				}
			});
		light->shadow->Unbind();
		Graphic::Blit(*light->shadow, *light->tbuffer,*tMaterial); 
	}
	glViewport(0, 0, Screen::width,Screen::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Light::ShaderSetting(Shader& shader)
{
	if (!shader.enableLighting)
		return;  

	for (Light* light : Light::lights)
	{
		if( !light->lightParametersChangedInThisFrame )
			continue;

		if (light->type == Light::Type::Directional)
		{
			string arrayName = "dirLights";
			const char* intensityName = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_INTENSITY));
			const char* positionName = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_POSITION));
			const char* colorName = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_COLOR));
			shader.setVec3(positionName, light->transform->position);
			shader.setColor(colorName, light->color);
			shader.setFloat(intensityName, light->setting.intensity);
			delete[] intensityName;
			delete[] positionName;
			delete[] colorName;

		}
		else if (light->type == Light::Type::Point)
		{
			string arrayName = "pointLights";
			char* intensityStr = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_INTENSITY));
			char* positionStr = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_POSITION));
			char* colorStr = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_COLOR));
			char* rangeStr = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_RANGE));
			char* constantStr = spring::misc::string2c((arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_CONSTANT));
			char* linearStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_LINEAR);
			char* quadraticStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_QUADRATIC);
			shader.setVec3(positionStr, light->transform->position);
			shader.setColor(colorStr, light->color);
			shader.setFloat(intensityStr, light->setting.intensity);
			shader.setFloat(rangeStr, light->setting.range);
			shader.setFloat(constantStr, light->setting.constant);
			shader.setFloat(linearStr, light->setting.linear);
			shader.setFloat(quadraticStr, light->setting.quadratic);
			delete[] intensityStr;
			delete[] positionStr;
			delete[] colorStr;
			delete[] rangeStr;
			delete[] constantStr;
			delete[] linearStr;
			delete[] quadraticStr;
		}
		else if (light->type == Light::Type::Spot)
		{
			string arrayName = "spotLights";
			char* intensityStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_INTENSITY);
			char* positionStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_POSITION);
			char* directionStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_DIRECTION);
			char* colorStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_COLOR);
			char* rangeStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_RANGE);
			char* constantStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_CONSTANT);
			char* linearStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_LINEAR);
			char* quadraticStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_QUADRATIC);
			char* cutoffStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_CUTOFF);
			char* outerCutoffStr = spring::misc::string2c(arrayName + '[' + to_string(light->lightId) + "]." + _LIGHT_OUTERCUTOFF);
			shader.setVec3(positionStr, light->transform->position);
			shader.setColor(colorStr, light->color);
			shader.setVec3(directionStr, light->transform->GetEulerangle());
			shader.setFloat(intensityStr, light->setting.intensity);
			shader.setFloat(rangeStr, light->setting.range);
			shader.setFloat(constantStr, light->setting.constant);
			shader.setFloat(linearStr, light->setting.linear);
			shader.setFloat(quadraticStr, light->setting.quadratic);
			shader.setFloat(cutoffStr, glm::cos(glm::radians(light->setting.spotAngle / 2.0f)));
			shader.setFloat(outerCutoffStr, glm::cos(glm::radians(light->setting.outterAngle / 2.0f)));
			delete[] intensityStr;
			delete[] positionStr;
			delete[] directionStr;
			delete[] colorStr;
			delete[] rangeStr;
			delete[] constantStr;
			delete[] linearStr;
			delete[] quadraticStr;
			delete[] cutoffStr;
			delete[] outerCutoffStr;
		}
		else
		{

		}
	}
}