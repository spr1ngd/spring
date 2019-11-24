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

		bool depthTest = true;
		bool depthWrite = true;
		GLenum depthFunc = GL_LESS;

		// todo : add stencil test
		bool stencilTest = false;

		bool cullface = true;
		GLenum cullfaceFunc = GL_BACK;

	public:
		enum RenderMode 
		{
			Point,
			Line,
			Fill
		};
		const char* name;
		Shader* shader;
		RenderMode renderMode = RenderMode::Fill;

		// shadow setting
		bool castShadow = true;
		bool receiveShadow = true;

		// instanced 
		bool enableGPUInstanced = false;

	private:
		GLenum GetPolygonMode();
	public:
		Material();
		Material(const char*vertexShaderFile,const char*fragmentShaderFile);
		Material(const char*vertexShaderFile,const char*fragmentShaderFile,const char* geometryShaderFile);
		Material(Shader* shader);

		void AlphaTestFunc( GLenum alphaTestFunc = GL_GREATER,float alphaTestRef = 0.5f );
		void EnableAlphaTest();

		void AlphaBlendFunc( GLenum srcFactor = GL_SRC_ALPHA,GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA);
		void EnableAlphaBlend();

		void DepthTestFunc( bool enable, GLenum func = GL_LESS , bool depthWrite = true);
		void EnableDepthTest();

		void StencilTestFunc();
		void EnableStencilTest();

		void CullFaceFunc( bool enabel, GLenum cullface = GL_BACK );
		void EnableCullFace();
	};
}