#pragma once
#include <vector>
#include "shader.h"

namespace spring 
{
	class Matrix4x4;
	class Texture;
	class Material
	{
	private:
		static std::vector<Material*> materials;
		static void Caching(Material* material);
		static void Flash(Material* material);

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

	private:
		std::vector<Texture*> texs;
		GLenum GetPolygonMode();

	public:
		static Material* defaultPBRMaterial;
		static Material* defaultLambertMaterial;

		Material();
		Material(Shader* shader);
		~Material();

		void AlphaTestFunc( GLenum alphaTestFunc = GL_GREATER,float alphaTestRef = 0.5f );
		void EnableAlphaTest();

		void AlphaBlendFunc( GLenum srcFactor = GL_SRC_ALPHA,GLenum dstFactor = GL_ONE_MINUS_SRC_ALPHA);
		void EnableAlphaBlend();

		void DepthTestFunc( bool enable, GLenum func = GL_LESS,bool enableDepthWrite = true);
		void EnableDepthTest();
		void EnableDepthWrite();

		void StencilTestFunc();
		void EnableStencilTest();

		void CullFaceFunc( bool enabel, GLenum cullface = GL_BACK );
		void EnableCullFace();

		// set textures
		void SetTexture(const char* texName,Texture* texture);
		void SetTextures(std::vector<Texture*> textures);

		void SetColor(const char* propertyName,const Colorf& color);
		void SetFloat(const char* propertyName,const float fValue);
		void SetInt(const char* propertyName,const int iValue);
		void SetBool(const char* propertyName,const bool bValue);
		void SetVec2(const char* propertyName,const Vector2& vec2);
		void SetVec3(const char* propertyName,const Vector3& vec3);
		void SetVec4(const char* propertyName,const Vector4& vec4);
		void SetMatrix(const char* propertyName,const Matrix4x4& matrix);
	};
}