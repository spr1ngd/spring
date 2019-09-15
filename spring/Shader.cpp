#include <fstream>
#include "NotImplementException.h"
#include "shader.h"
#include "console.h"

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
	this->setEngineEnvironment();
}

#pragma region shader program methods

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
	GLuint mLocation = glGetUniformLocation(this->program, MATRIX_M);
	this->locations.insert(pair<const char*, GLuint>(MATRIX_M, mLocation));

	GLuint vLocation = glGetUniformLocation(this->program, MATRIX_V);
	this->locations.insert(pair<const char*, GLuint>(MATRIX_V, vLocation));

	GLuint pLocation = glGetUniformLocation(this->program, MATRIX_P);
	this->locations.insert(pair<const char*, GLuint>(MATRIX_P, pLocation));

	GLuint veretxLocation = glGetAttribLocation(this->program, VERTEX);
	this->locations.insert(pair<const char*, GLuint>(VERTEX, veretxLocation));

	GLuint normalLocation = glGetAttribLocation(this->program, NORMAL);
	this->locations.insert(pair<const char*, GLuint>(NORMAL, normalLocation));

	GLuint texcoordLocation = glGetAttribLocation(this->program, TEXCOORD);
	this->locations.insert(pair<const char*, GLuint>(TEXCOORD, texcoordLocation));

	GLuint mainTextureLocation = glGetUniformLocation(this->program,MAIN_TEX);
	this->locations.insert(pair<const char*,GLuint>(MAIN_TEX,mainTextureLocation));

	GLuint mainCubemapLocation = glGetUniformLocation(this->program,MAIN_CUBEMAP);
	this->locations.insert(pair<const char*,GLuint>(MAIN_CUBEMAP,mainCubemapLocation));

	GLuint mainColorLocation = glGetUniformLocation(this->program,MAIN_COLOR);
	this->locations.insert(pair<const char*,GLuint>(MAIN_COLOR,mainColorLocation));

	GLuint ambientColorLocation = glGetUniformLocation(this->program,AMBIENT_COLOR);
	this->locations.insert(pair<const char*,GLuint>(AMBIENT_COLOR,ambientColorLocation));
}

GLuint Shader::getLocation(const char* name)
{
	auto pair = this->locations.find(name);
	if (pair == this->locations.end())
		return -1;
	return pair->second;
}

void Shader::use() 
{
	glUseProgram(this->program);
	this->setShaderValues();
}

void Shader::disuse() 
{
	glUseProgram(0);
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

#pragma endregion

void Shader::setBool(const char* name, GLboolean value) 
{
	GLuint location = this->getLocation(name);
	throw new NotImplementException();
}

void Shader::setMat4(const char* name, glm::mat4 value) 
{
	GLuint location = this->getLocation(name);
	throw new NotImplementException();
}

void Shader::setVec3(const char* name, glm::vec3 vec3) 
{
	GLuint location = this->getLocation(name);
	throw new NotImplementException();
}

void Shader::setInt(const char* name, GLint value)
{
	GLuint location = this->getLocation(name);
	auto pair = this->ints.find(location);
	if (pair == this->ints.end())
	{
		this->ints.insert(std::pair<GLuint,GLuint>(location, value));
		return;
	}
	this->ints[location] = value;
}

void Shader::setFloat(const char* name, GLfloat value)
{
	GLuint location = this->getLocation(name);
	auto pair = this->floats.find(location);
	if (pair == this->floats.end())
	{
		this->floats.insert(std::pair<GLuint,GLfloat>(location,value));
		return;
	}
	this->floats[location] = value;
}

void Shader::setColor(const char* name, Color color) 
{
	GLuint location = this->getLocation(name);
	auto pair = this->colors.find(location);
	if (pair == this->colors.end())
	{
		this->colors.insert(std::pair<GLuint,Color>(location, color));
		return;
	}
	this->colors[location] = color;
}

void Shader::setShaderValues() 
{
	for (auto pair : this->ints) 
		glUniform1i(pair.first, pair.second);

	for (auto pair : this->floats)
		glUniform1f(pair.first, pair.second);

	for (auto pair : this->colors)
	{
		Color color = pair.second;
		const GLfloat value[4] = { color.r / 255.0f ,color.g / 255.0f,color.b / 255.0f,color.a / 255.0f };
		glUniform4fv(pair.first, 1, value);
	}
}

void Shader::setEngineEnvironment() 
{
	this->setColor(AMBIENT_COLOR,Environment::ambient.color);
}