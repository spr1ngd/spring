#pragma once
#include "shader.h"
#include "vector3.h"

namespace spring 
{
	class Material
	{
	public:
		enum CullFace 
		{
			None,
			Back,
			Front,
			FrontAndBack
		};
		enum RenderMode 
		{
			Point,
			Line,
			Fill
		};
		const char* name;
		Shader* shader;
		CullFace cullface = CullFace::None;
		RenderMode renderMode = RenderMode::Fill;

		bool depthTest = true;
		bool alphaTest = true;

		GLenum GetPolygonMode( RenderMode renderMode )    
		{
			switch (renderMode)
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
	public:
		Material();
		Material(const char*verexShaderFile,const char*fragmentShaderFile);
		Material(Shader* shader);
		void EnableCullFace() 
		{
			switch (this->cullface) 
			{
			case CullFace::None:
				glDisable(GL_CULL_FACE);
				glPolygonMode(GL_FRONT_AND_BACK, GetPolygonMode(renderMode));
				break;
			case CullFace::Back:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glPolygonMode(GL_FRONT, GetPolygonMode(renderMode));
				break;
			case CullFace::Front:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				glPolygonMode(GL_BACK, GetPolygonMode(renderMode));
				break;
			case CullFace::FrontAndBack:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				break;
			}
		}

		// todo : set value for shader 's attribute and uniform 
		float* GetVec3( const char* nameID );
		void SetVec3( const char* nameID,float* value);
	};
}