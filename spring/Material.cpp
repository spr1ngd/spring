#include "material.h"
#include "texture.h"
#include "console.h"

using namespace std;
using namespace spring;

std::vector<Material*> Material::materials;
Material* Material::defaultPBRMaterial = nullptr;// new Material(Shader::Load("pbs/pbs.vs", "pbs/pbs(ibl).fs"));
Material* Material::defaultLambertMaterial = nullptr;// new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));

Material::Material() 
{
	Material::Caching(this);
}
Material::Material(Shader* shader) 
{
	this->shader = shader;
	Material::Caching(this);
}

Material::~Material() 
{
	if (nullptr != this->shader)
		delete this->shader;
	Flash(this);
}

#pragma region material basic properties setting 

void Material::SetTexture(const char* texName, Texture* texture)
{
	if (nullptr == this->shader || nullptr == texture)
		return;
	this->shader->setTexture(texName, texture->textureId);
}

void Material::SetTextures(std::vector<Texture*> textures)
{
	for (Texture* texture : textures)
		this->SetTexture(texture->textureName, texture);
}

void Material::SetColor(const char* propertyName, const Colorf& color) 
{
	this->shader->setColor(propertyName, color);
}
void Material::SetFloat(const char* propertyName, const float fValue) 
{
	this->shader->setFloat(propertyName, fValue);
}
void Material::SetInt(const char* propertyName, const int iValue) 
{
	this->shader->setInt(propertyName, iValue);
}
void Material::SetBool(const char* propertyName, const bool bValue) 
{
	this->shader->setBool(propertyName, bValue);
}

void Material::SetVec2(const char* propertyName, const Vector2& vec2) 
{
	this->shader->setVec2(propertyName, vec2);
}

void Material::SetVec3(const char* propertyName, const Vector3& vec3) 
{
	this->shader->setVec3(propertyName, vec3);
}

void Material::SetVec4(const char* propertyName, const Vector4& vec4) 
{
	this->shader->setVec4(propertyName, vec4);
}

void Material::SetMatrix(const char* propertyName, const Matrix4x4& matrix) 
{
	throw "not implement.";
}

#pragma endregion

void Material::AlphaTestFunc(GLenum alphaTestFunc, float alphaTestRef ) 
{
	this->alphaTest = true;
	this->alphaFunc = alphaTestFunc;
	this->alphaRef = alphaTestRef;
}
void Material::EnableAlphaTest() 
{
	if (this->alphaTest == true) 
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(this->alphaFunc, this->alphaRef);
	}
	else 
	{
		glDisable(GL_ALPHA_TEST);
	}
}

void Material::AlphaBlendFunc(GLenum srcFactor, GLenum dstFactor) 
{
	this->blend = true;
	this->srcFactor = srcFactor;
	this->dstFactor = dstFactor;
}
void Material::EnableAlphaBlend() 
{
	if (this->blend == true)
	{
		glEnable(GL_BLEND);
		glBlendFunc(this->srcFactor, this->dstFactor);
	}
	else 
	{
		glDisable(GL_BLEND);
	}
}

void Material::DepthTestFunc(bool enable, GLenum func,bool enableDepthWrite)
{
	this->depthTest = enable;
	this->depthWrite = enableDepthWrite;
	this->depthFunc = func;
}
void Material::EnableDepthTest()
{
	if (this->depthTest == true) 
	{
		glEnable(GL_DEPTH_TEST);
	}
	else 
	{
		glDisable(GL_DEPTH_TEST);
	}
}
void Material::EnableDepthWrite()  
{
	if (this->depthWrite == true)
	{
		glDepthFunc(this->depthFunc);
		glDepthMask(GL_TRUE);
	}
	else
	{
		glDepthMask(GL_FALSE);
	}
}

void Material::StencilTestFunc() 
{

}
void Material::EnableStencilTest() 
{
	if (this->stencilTest == true) 
	{
		glEnable(GL_STENCIL_TEST);
	}
	else 
	{
		glDisable(GL_STENCIL_TEST);
	}
}

void Material::CullFaceFunc( bool enable,GLenum cullfaceFunc ) 
{
	this->cullface = enable;
	this->cullfaceFunc = cullfaceFunc;
	
}
void  Material::EnableCullFace() 
{
	if (this->cullface == true) 
	{
		glEnable(GL_CULL_FACE);
		glCullFace(this->cullfaceFunc);
	}
	else 
	{
		glDisable(GL_CULL_FACE);
	}

	switch (this->cullfaceFunc)
	{
	case GL_NONE:
		glPolygonMode(GL_FRONT_AND_BACK, GetPolygonMode());
		break;
	case GL_BACK:
		glPolygonMode(GL_FRONT, GetPolygonMode());
		break;
	case GL_FRONT:
		glPolygonMode(GL_BACK, GetPolygonMode());
		break;
	}
}

GLenum Material::GetPolygonMode()
{
	switch (this->renderMode)
	{
	case spring::Material::Point:
		return GL_POINT;
	case spring::Material::Line:
		return GL_LINE;
	case spring::Material::Fill:
		return GL_FILL;
	default:
		return GL_FILL;
	}
}

#pragma region caching and flash material object.

void Material::Caching(Material* material) 
{
	materials.push_back(material);
}

void Material::Flash(Material* material) 
{
	for (vector<Material*>::iterator item = materials.begin(); item != materials.end();item++) 
	{
		if (*item == material)
		{
			materials.erase(item);
			return;
		}
	}
}

#pragma endregion
