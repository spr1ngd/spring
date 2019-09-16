#pragma once
#include "glew.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"  
#include <map>
#include "color.h"
#include "vector3.h"
#include "vector4.h"
#include "environment.h"

#define MATRIX_M "M"
#define MATRIX_V "V"
#define MATRIX_P "P"
#define MATRIX_NM "NM"

#define VERTEX "vertex"
#define NORMAL "normal"
#define TEXCOORD "texcoord"

#define MAIN_TEX "Main_Texture"
#define MAIN_CUBEMAP "Main_Cubemap"
#define MAIN_COLOR "Main_Color"

// ambient system properties
#define AMBIENT_COLOR "AmbientColor"

// lighting properties
#define LIGHT_COLOR "light.color"
#define LIGHT_POSITION "light.position"
#define LIGHT_INSTENSITY "light.intensity"
#define LIGHT_DIRECTION "light.direction"
#define LIGHT_CUTOFF "light.cutoff"
#define LIGHT_RANGE "light.range"
#define LIGHT_ATTENUATION "light.attenuation"

// camera properties
#define CAMERA_POSITION "CameraPosition"

using namespace std;

namespace spring 
{
	class Shader
	{
	private:
		std::map<const char*, GLuint> locations;
		std::map<GLenum, GLuint> shaders;
		void linkProgram();
		GLuint compileShader(GLenum shaderType, const char* shaderFilePath);
		char* loadShaderFile(const char* shaderFilePath);
		void initializeLocation();

		map<GLuint, Color> colors;
		map<GLuint, GLuint> ints;
		map<GLuint, GLfloat> floats;
		map<GLuint, Vector3> vec3Map;
		map<GLuint, Vector4> vec4Map;
		map<GLuint, GLuint> textures;
		map<GLuint, glm::mat4> mat4Map;

		void setShaderValues();
		void setEngineEnvironment();

	public:
		GLuint program;

		Shader();
		Shader(const char*vertex,const char*fragment );
		void use();
		void disuse();
		GLuint getLocation(const char*name);

		void setBool(const char* name, GLboolean value);
		void setInt(const char* name, GLint value);
		void setFloat(const char* name, GLfloat value);
		void setMat4(const char* name, glm::mat4 value);

		void setVec3(const char* name, Vector3 vec3);
		void setVec4(const char* name, Vector4 vec4);
		void setColor(const char* name, Color color);
		void setTexture(const char*name, GLuint texture);
	};
}