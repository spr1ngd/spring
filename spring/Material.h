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
	public:
		Material();
		Material(const char*verexShaderFile,const char*fragmentShaderFile);
		Material(Shader* shader);

		// todo : set value for shader 's attribute and uniform 
		float* GetVec3( const char* nameID );
		void SetVec3( const char* nameID,float* value);

		void EnableCullFace() 
		{
			switch (this->cullface) 
			{
			case CullFace::None:
				glDisable(GL_CULL_FACE);
				break;
			case CullFace::Back:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				glPolygonMode(GL_BACK, renderMode);
				break;
			case CullFace::Front:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				glPolygonMode(GL_FRONT, renderMode);
				break;
			case CullFace::FrontAndBack:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT_AND_BACK);
				glPolygonMode(GL_FRONT_AND_BACK, renderMode);
				break;
			}
		}
	};
}