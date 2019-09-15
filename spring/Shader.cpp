#include <fstream>
#include "notimplementexception.h"
#include "console.h"
#include "shader.h"
#include "light.h"

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

#pragma region lighting properties

	GLuint lightColorLocation = glGetUniformLocation(this->program,LIGHT_COLOR);
	this->locations.insert(pair<const char*,GLuint>(LIGHT_COLOR,lightColorLocation));

	GLuint lightIntensityLocation = glGetUniformLocation(this->program,LIGHT_INSTENSITY);
	this->locations.insert(pair<const char*,GLuint>(LIGHT_INSTENSITY,lightIntensityLocation));

	GLuint lightPositionLocation = glGetUniformLocation(this->program,LIGHT_POSITION);
	this->locations.insert(pair<const char*,GLuint>(LIGHT_POSITION,lightPositionLocation));

	GLuint lightDirectionLocation = glGetUniformLocation(this->program,LIGHT_DIRECTION);
	this->locations.insert(pair<const char*,GLuint>(LIGHT_DIRECTION,lightDirectionLocation));

#pragma endregion

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

void Shader::setVec3(const char* name, Vector3 value)
{
	GLuint location = this->getLocation(name);
	auto pair = this->vec3Map.find(location);
	if (pair == this->vec3Map.end())
	{
		this->vec3Map.insert(std::pair<GLuint,Vector3>(location,value));
		return;
	}
	this->vec3Map[location] = value;
}

//void Shader::setVec4(const char* name, const GLfloat* value) 
//{
//	GLuint location = this->getLocation(name);
//}

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
		const float value[4] = { color.r / 255.0f ,color.g / 255.0f,color.b / 255.0f,color.a / 255.0f };
		glUniform4fv(pair.first, 1, value);
	}

	for (auto pair : this->vec3Map)
	{
		Vector3 vec3 = pair.second;
		const float value[3] = {vec3.x,vec3.y,vec3.z};
		glUniform3fv(pair.first, 1, value);
	}
}

void Shader::setEngineEnvironment() 
{
	this->setColor(AMBIENT_COLOR,Environment::ambient.color);

	// todo : set lighting system parameters in here temporary
	if (Light::main != nullptr)
	{
		this->setFloat(LIGHT_INSTENSITY, Light::main->intensity);
		this->setColor(LIGHT_COLOR, Light::main->color);
		this->setVec3(LIGHT_DIRECTION, Light::main->transform->position);
		this->setVec3(LIGHT_POSITION, Light::main->transform->position);
	}
	else 
	{
		Console::WarningFormat("scene does not have light.");
	}
}