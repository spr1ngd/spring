#include "environment.h"
#include "shader.h"

using namespace spring;

Environment::AmbientSetting Environment::ambient;
Environment::ShadowSetting Environment::shadow;

const Environment::AmbientSetting& Environment::GetAmbientSetting()
{
	return Environment::ambient;
}

const Environment::ShadowSetting& Environment::GetShadowSetting() 
{
	return Environment::shadow;
}

void Environment::SetAmbientSetting(Color ambientColor) 
{
	Environment::ambient.color = ambientColor;

	Shader::ForEach([&](Shader* shader) 
		{
			shader->setColor(AMBIENT_COLOR, Environment::ambient.color);
		});
}

void Environment::SetShodowSetting(ShadowSetting::SampleLevel shadowSampleLevel) 
{
	Environment::shadow.sample = shadowSampleLevel;

	Shader::ForEach([&](Shader* shader)
		{
			shader->setInt(SHADOW_SAMPLELEVEL, Environment::shadow.sample);
		});
}