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

void Material::DepthTestFunc(bool enable, GLenum func)
{
	this->depthTest = enable;
	this->depthWrite = depthWrite;
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
void Material::EnableDepthWrite( bool enable )  
{
	this->depthWrite = enable;
	glDepthFunc(this->depthFunc);
	if (this->depthWrite == true)
	{
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
