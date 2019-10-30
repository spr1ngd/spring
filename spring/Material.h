#pragma once
#include <vector>
#include "shader.h"
#include "vector3.h"

namespace spring 
{
	class Material
	{
	private:
		static std::vector<Material*> materials;

		static void Caching(Material* material);
		static void Flash(Material* material);

	private:
		bool alphaTest = false;
		GLenum alphaFunc = GL_GREATER;
		float alphaRef = 0.5f;

		bool blend = false;
		GLenum srcFactor = GL_SRC_ALPHA;
		GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA;
	public:
		friend class MeshRenderer;
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

		void AlphaTest( GLenum alphaTestFunc = GL_GREATER,float alphaTestRef = 0.5f );
		void BlendFunc( GLenum srcFactor = GL_SRC_ALPHA,GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA);
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
	};
}