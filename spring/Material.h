#pragma once
#include "shader.h"
#include "vector3.h"

namespace spring 
{
	class Material
	{
	public:
		const char* name;
		Shader* shader;
		bool depthTest = true;
		bool alphaTest = true;
	public:
		Material();
		Material(const char*verexShaderFile,const char*fragmentShaderFile);
		Material(Shader* shader);

		// todo : set value for shader 's attribute and uniform 
		float* GetVec3( const char* nameID );
		void SetVec3( const char* nameID,float* value);
	};
}