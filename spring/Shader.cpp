#include "Shader.h"
#include <fstream>
#include "Console.h"

using namespace std;
using namespace spring;

Shader::Shader() 
{
	// todo : use default shader?
}

Shader::Shader( const char*vertexShader,const char*fragmentShader ) 
{
	GLuint vertex = this->compileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fragment = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	shaders.insert(pair<GLenum, GLuint>(GL_VERTEX_SHADER, vertex));
	shaders.insert(pair<GLenum, GLuint>(GL_FRAGMENT_SHADER, fragment));
	this->linkProgram();
	this->initializeLocation();
}
 

void Shader::linkProgram()
{
	GLuint program = glCreateProgram();
	glAttachShader(program, this->shaders[GL_VERTEX_SHADER]);
	glAttachShader(program, this->shaders[GL_FRAGMENT_SHADER]);
	glLinkProgram(program);

	int success;
	char logInfo[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(program, 512, NULL, logInfo);
		Console::Error(logInfo);
	}
	this->program = program;
	// todo : delete compiled shader.
}

void Shader::initializeLocation()
{
	GLuint mLocation = glGetAttribLocation(this->program, MATRIX_M);
	this->locations.insert(pair<const char*, GLuint>(MATRIX_M, mLocation));

	GLuint vLocation = glGetAttribLocation(this->program, MATRIX_V);
	this->locations.insert(pair<const char*, GLuint>(MATRIX_V, vLocation));

	GLuint pLocation = glGetAttribLocation(this->program, MATRIX_P);
	this->locations.insert(pair<const char*, GLuint>(MATRIX_P, pLocation));

	GLuint veretxLocation = glGetAttribLocation(this->program, VERTEX);
	this->locations.insert(pair<const char*, GLuint>(VERTEX, veretxLocation));

	GLuint normalLocation = glGetAttribLocation(this->program, NORMAL);
	this->locations.insert(pair<const char*, GLuint>(NORMAL, normalLocation));

	GLuint texcoordLocation = glGetAttribLocation(this->program, TEXCOORD);
	this->locations.insert(pair<const char*, GLuint>(TEXCOORD, texcoordLocation));
}

GLuint Shader::getLocation(const char* name)
{
	auto pair = this->locations.find(name);
	// todo : read security code.
	return pair->second;
}

void Shader::use() 
{
	glUseProgram(this->program);
}

void Shader::disuse() 
{
	glUseProgram(0);
}

void Shader::setFloat(const char* name, GLfloat value) 
{

}

GLuint Shader::compileShader( GLenum shaderType,const char*shaderFilePath )
{
	const char* source = loadShaderFile(shaderFilePath);
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source,NULL);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		Console::Error(infoLog);
	}
	return shader;
}

char* Shader::loadShaderFile( const char*shaderFilePath )
{
	ifstream shaderFile;
	int length;
	shaderFile.open(shaderFilePath, ios::in|ios::binary);
	if (!shaderFile.good()) 
	{
		Console::Error(shaderFilePath);
		Console::Error("shader file is not exist.");
		return NULL;
	}
	shaderFile.seekg(0, ios::end);
	length = shaderFile.tellg();
	shaderFile.seekg(ios::beg);
	char* buffer = new char[length+1];
	shaderFile.read(buffer, length);
	buffer[length] = '\0';
	shaderFile.close();
	return buffer;
} 