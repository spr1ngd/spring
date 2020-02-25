#pragma once
#include "GL/glew.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"  
#include <map>
#include <vector>
#include "color.h"
#include "vector3.h"
#include "vector4.h"
#include "environment.h"
#include "materialtexture.h"
#include "cubemap.h"

#define VERTEX "vertex"
#define NORMAL "normal"
#define TEXCOORD "texcoord"
#define COLOR "color"

#define MAIN_TEX "Main_Texture"
#define SECONDARY_TEX "Secondary_Texture"
#define MAIN_CUBEMAP "Main_Cubemap"
#define MAIN_COLOR "Main_Color"

// ambient system properties
#define AMBIENT_COLOR "AmbientColor"
#define SHADOWMAP "ShadowMap"
#define SHADOW_SAMPLELEVEL "SampleLevel"

// lighting properties
#define LIGHT_COLOR "light.color"
#define LIGHT_POSITION "light.position"
#define LIGHT_INSTENSITY "light.intensity"
#define LIGHT_DIRECTION "light.direction"
#define LIGHT_CUTOFF "light.cutoff"
#define LIGHT_RANGE "light.range"
#define LIGHT_ATTENUATION "light.attenuation"

// camera properties
#define MATRIX_M "M"
#define MATRIX_V "V"
#define MATRIX_P "P"
#define MATRIX_NM "NM"
#define MATRIX_MVP "MVP"

#define CAMERA_POSITION "CameraPosition"
#define WorldSpaceCameraPos "WorldSpaceCameraPos"

// matrix 
#define World2Object "World2Object"
#define Object2World "Object2World"

// time type
#define _Time "_Time"

using namespace std;

namespace spring 
{
	class Shader
	{
	private:
		static std::vector<Shader*> cachingShaders;

		static void Caching(Shader* shader);
		static void Flash(Shader* shader);
	public:
		static Shader* error;
		static Vector4 shaderTimer;
		static Shader* Load(const char* vertexShaderName,const char* fragmentShaderName);

	private:
		std::map<const char*, unsigned int> locations;
		char* loadShaderFile(const char* shaderFilePath);
		void initializeLocation();

		bool compile(GLenum shaderType,const char* filePath,unsigned int& shader);
		bool link(unsigned int vertexShader,unsigned int fragmentShader);
		bool link(unsigned int vertexShader, unsigned int fragmentShader,unsigned int geometryShader);


		void setShaderValues();
		void setEngineEnvironment();
		void setLighting();
		void setTime();

	public:
		map<unsigned int, Colorf> colors;
		map<unsigned int, GLuint> ints;
		map<unsigned int, GLfloat> floats;
		map<unsigned int, Vector2> vec2Map;
		map<unsigned int, Vector3> vec3Map;
		map<unsigned int, Vector4> vec4Map;
		map<unsigned int, glm::mat4> mat4Map;

		map<unsigned int, MaterialTexture> textures;
		map<unsigned int, Cubemap*> cubemaps;

		GLuint program;
		bool receiveShadow = true;

		Shader();
		Shader(const char*vertex,const char*fragment );
		Shader(const char*vertex,const char*fragment,const char* geometry);

		void use();
		void disuse();
		unsigned int getAttribLocation(const char* name);
		unsigned int getUniformLocation(const char* name);
		unsigned int getLocation(const char*name);
		char* getUniformName(unsigned int location);

		void setBool(const char* name, GLboolean value);
		void setInt(const char* name, GLint value);
		void setFloat(const char* name, GLfloat value);
		void setMat4(const char* name, glm::mat4 value);

		void setVec2(const char*name, Vector2 vec2);
		void setVec3(const char* name, Vector3 vec3);
		void setVec4(const char* name, Vector4 vec4);
		void setColor(const char* name, Color color);
		void setColor(const char* name, Colorf color);

		void setTexture(const char*name, GLuint texture);
		void setTilling(const char*name, Vector2 tilling);
		void setOffset(const char*name, Vector2 offset);
		void setCubemap(const char*name, Cubemap* cubemap);
	};
}