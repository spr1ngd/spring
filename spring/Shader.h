#pragma once
#include "glew.h"
#include "Glm/glm.hpp"
#include "Glm/ext.hpp"  
#include <map>

#define MATRIX_M "M"
#define MATRIX_V "V"
#define MATRIX_P "P"

#define VERTEX "vertex"
#define NORMAL "normal"
#define TEXCOORD "texcoord"

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

	public:
		GLuint program;

		Shader();
		Shader(const char*vertex,const char*fragment );
		void use();
		void disuse();

		void setBool(const char* name, GLboolean value);
		void setInt(const char* name, GLint value);
		void setFloat(const char* name, GLfloat value);
		void setMat4(const char* name, glm::mat4 value);
		void setVec3(const char* name, glm::vec3 value);

		GLuint getLocation(const char*name);
	};
}