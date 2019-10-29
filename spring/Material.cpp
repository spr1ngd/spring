#include "material.h"
#include "console.h"

using namespace std;
using namespace spring;

std::vector<Material*> Material::materials;

Material::Material() 
{
	Material::Caching(this);
}

Material::Material(Shader* shader) 
{
	this->shader = shader;
	Material::Caching(this);
}

Material::Material(const char* verexShaderFile, const char* fragmentShaderFile)
{
	Console::Error(verexShaderFile);
	this->shader = new Shader(verexShaderFile,fragmentShaderFile);
	Material::Caching(this);
}

float* Material::GetVec3(const char* nameID) 
{
	return nullptr;
}

void Material::SetVec3(const char* nameID, float* value) 
{

}

#pragma region caching and flash material object.

void Material::Caching(Material* material) 
{
	materials.push_back(material);
}

void Material::Flash(Material* material) 
{
	for (vector<Material*>::iterator item = materials.begin(); item != materials.end();) 
	{
		materials.erase(item);
		return;
	}
}

#pragma endregion
