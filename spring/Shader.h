#pragma once
#include "GL/glew.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"  
#include <map>
#include <vector>
#include <functional>
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
#define HEIGHT_TEX "Height_Texture"
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
	template<typename T>
	struct ShaderParams 
	{
		int location;
		T value;
	};

	typedef ShaderParams<Colorf> ShaderColorfParams;
	typedef ShaderParams<Vector2> ShaderVec2Params;
	typedef ShaderParams<Vector3> ShaderVec3Params;
	typedef ShaderParams<Vector4> ShaderVec4Params;
	typedef ShaderParams<int> ShaderIntParams;
	typedef ShaderParams<bool> ShaderBoolParams;
	typedef ShaderParams<float> ShaderFloatParams;
	typedef ShaderParams<glm::mat4> ShaderMat4Params;
	typedef ShaderParams<MaterialTexture> ShaderTextureParams;
	typedef ShaderParams<Cubemap> ShaderCubemapParams;

	class Shader
	{
	private:
		static std::vector<Shader*> cachingShaders;

		static void Caching(Shader* shader);
		static void Flash(Shader* shader);
	public:
		static Shader* error;
		static Vector4 shaderTimer;
		static Shader* Load(const char* shaderName);
		static Shader* Load(const char* vertexShaderName,const char* fragmentShaderName,const char* geometryShader = nullptr);
		static void ForEach(std::function<void(Shader*)> func);

	private:
		char* loadShaderFile(const char* shaderFilePath);
		void initializeLocation();

		bool compile(GLenum shaderType,const char* filePath,unsigned int& shader);
		bool link(unsigned int vertexShader, unsigned int fragmentShader);
		bool link(unsigned int vertexShader, unsigned int fragmentShader,unsigned int geometryShader);

		void setShaderValues();
		void setEngineEnvironment();
		void setLighting(); 

	public:
		std::map<const char*, int> locations;
		char* vertexShaderName;
		char* fragmentShaderName;
		char* geometryShaderName;

		map<unsigned int, Colorf> colors;
		map<const char*, ShaderColorfParams> _colors;

		map<unsigned int, GLuint> ints;
		map<const char*, ShaderIntParams> _ints;

		map<unsigned int, bool> bools;
		map<const char*, ShaderBoolParams> _bools;

		map<unsigned int, GLfloat> floats;
		map<const char*, ShaderFloatParams> _floats;

		map<unsigned int, Vector2> vec2Map;
		map<const char*, ShaderVec2Params> _vec2s;

		map<unsigned int, Vector3> vec3Map;
		map<const char*, ShaderVec3Params> _vec3s;

		map<unsigned int, Vector4> vec4Map;
		map<const char*, ShaderVec4Params> _vec4s;

		map<unsigned int, glm::mat4> mat4Map;
		map<const char*, ShaderMat4Params> _mat4s;

		map<unsigned int, MaterialTexture> textures;
		map<const char*, ShaderTextureParams> _textures;

		map<unsigned int, Cubemap*> cubemaps;
		map<const char*, ShaderCubemapParams> _cubemaps;

		GLuint program;
		bool lightingIntialized = false;
		bool receiveShadow = true;
		bool enableLighting = true;

		Shader();
		Shader(const char*vertex,const char*fragment,const char* geometry = nullptr);
		~Shader();

		void use();
		void disuse();
		unsigned int getAttribLocation(const char* name);
		int getUniformLocation(const char* name);
		const char* getUniformName(unsigned int location);

		void setBool(const char* name, bool value);
		bool getBool(const char* name);

		void setInt(const char* name, GLint value);
		int getInt(const char* name);

		void setFloat(const char* name, GLfloat value);
		float getFloat(const char* name);

		void setMat4(const char* name, glm::mat4 value);

		void setVec2(const char*name, Vector2 vec2);
		Vector2 getVec2(const char* name);

		void setVec3(const char* name, Vector3 vec3);
		Vector3 getVec3(const char* name);

		void setVec4(const char* name, Vector4 vec4);
		Vector4 getVec4(const char* name);

		void setColor(const char* name, Color color);
		Color getColor(const char* name);

		void setColor(const char* name, Colorf color);
		Colorf GetColorf(const char* name);

		void setTexture(const char* name, GLuint texture);
		int getTexture(const char* name);

		void setTilling(const char* name, Vector2 tilling);
		Vector2 getTilling(const char* name);

		void setOffset(const char* name, Vector2 offset);
		Vector2 getOffset(const char* name);

		void setCubemap(const char* name, Cubemap* cubemap);
		int getCubemap(const char* name);
	};
}