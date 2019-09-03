#include "Material.h"

using namespace spring;

Material::Material() 
{

}

Material::Material(Shader* shader) 
{
	this->shader = shader;
}

Material::Material(const char* verexShaderFile, const char* fragmentShaderFile)
{
	this->shader = new Shader(verexShaderFile,fragmentShaderFile);
}

float* Material::GetVec3(const char* nameID) 
{
	return nullptr;
}

void Material::SetVec3(const char* nameID, float* value) 
{

}