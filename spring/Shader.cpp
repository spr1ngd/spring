#include <fstream>
#include "notimplementexception.h"
#include "console.h"
#include "shader.h"
#include "light.h"
#include "camera.h"
#include <string>
#include "texture.h"
#include "textureloader.h"
#include "misc.h"
#include "graphicprofiler.h"

using namespace std;
using namespace spring;

std::vector<Shader*> Shader::cachingShaders;
Vector4 Shader::shaderTimer;
Shader* Shader::error;

Shader::Shader()
{
	Shader::Caching(this);
}
Shader::Shader(const char* vertexShader, const char* fragmentShader, const char* geometryShader)
{
	bool success = true;
	unsigned int vertex_shader = -1, fragment_shader = -1, geometry_shader = -1;
	success &= this->compile(GL_VERTEX_SHADER, vertexShader, vertex_shader);
	success &= this->compile(GL_FRAGMENT_SHADER, fragmentShader, fragment_shader);
	if (nullptr != geometryShader)
	{
		success &= this->compile(GL_GEOMETRY_SHADER, geometryShader, geometry_shader);
		success &= this->link(vertex_shader, fragment_shader, geometry_shader);
	}
	else success &= this->link(vertex_shader, fragment_shader);
	if (success == false)
	{
		PRINT_ERROR("shader error , replaced by default error shader.");
		if (nullptr == Shader::error)
			Shader::error = Shader::Load("spring/error.vs", "spring/error.fs");
		this->program = Shader::error->program;
	}
	this->vertexShaderName = new char[strlen(vertexShader)];
	strcpy_s(this->vertexShaderName, strlen(vertexShader) + 1, vertexShader);
	this->fragmentShaderName = new char[strlen(fragmentShader)];
	strcpy_s(this->fragmentShaderName, strlen(fragmentShader) + 1, fragmentShader);
	this->initializeLocation();
	Shader::Caching(this);
}
Shader::~Shader() 
{
	Flash(this);
}

#pragma region shader compile / link / use 

bool Shader::compile(GLenum shaderType, const char* filePath, unsigned int& shader)
{
	const char* source = this->loadShaderFile(filePath);
	unsigned int shaderProgram = glCreateShader(shaderType);
	glShaderSource(shaderProgram, 1, &source, NULL);
	glCompileShader(shaderProgram);
	delete source;
	int success;
	char infoLog[512];
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		PRINT_ERROR("[%s] complie failed : %s", filePath,infoLog);
		return false;
	}
	shader = shaderProgram;
	return true;
}

bool Shader::link(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	int success;
	char logInfo[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, logInfo);
		PRINT_ERROR("%s", logInfo);
		return false;
	}
	this->program = shaderProgram;
	return true;
}

bool Shader::link(unsigned int vertexShader, unsigned int fragmentShader, unsigned int geometryShader)
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, geometryShader);
	glLinkProgram(shaderProgram);
	int success;
	char logInfo[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, logInfo);
		PRINT_ERROR("%s", logInfo);
		return false;
	}
	this->program = shaderProgram;
	return true;
}

void Shader::initializeLocation()
{
	this->getUniformLocation(MATRIX_M);
	this->getUniformLocation(MATRIX_V);
	this->getUniformLocation(MATRIX_P);
	this->getUniformLocation(MATRIX_NM);
	this->getUniformLocation(MAIN_TEX);
	this->getUniformLocation(HEIGHT_TEX);
	this->getUniformLocation(MAIN_CUBEMAP);
	this->getUniformLocation(MAIN_COLOR);
	this->getUniformLocation(AMBIENT_COLOR);

	this->getUniformLocation(LIGHT_COLOR);
	this->getUniformLocation(LIGHT_INSTENSITY);
	this->getUniformLocation(LIGHT_POSITION);
	this->getUniformLocation(LIGHT_DIRECTION);
}

unsigned int Shader::getAttribLocation(const char* name) 
{
	return glGetAttribLocation(this->program, name);
}

unsigned int Shader::getUniformLocation(const char* name) 
{
// 	for (auto pair = this->locations.begin(); pair != this->locations.end(); pair++)
// 	{
// 		if (strcmp(pair->first, name) == 0)
// 			return pair->second;
// 	}
// 	int location = glGetUniformLocation(this->program,name);
// 	char* key = new char[strlen(name)];
// 	strcpy_s(key, strlen(name) + 1, name);
// 	this->locations.insert(std::pair<const char*, int>(key, location));
// 	return location;
	return glGetUniformLocation(this->program,name);
}

const char* Shader::getUniformName(unsigned int location)
{
	for (auto pair : this->locations)
	{
		if (pair.second == location)
			return pair.first;
	}
	return nullptr;
}

void Shader::use()
{
	glUseProgram(this->program);

	GraphicProfiler::BeginSample("lighting setting");
	this->setLighting();
	GraphicProfiler::EndSample();

	this->setEngineEnvironment();

	GraphicProfiler::BeginSample("shader parameters setting");
	this->setShaderValues();
	GraphicProfiler::EndSample();
	
	GraphicProfiler::BeginSample("shader time setting");
	this->setTime();
	GraphicProfiler::EndSample();
}

void Shader::disuse() 
{
	glUseProgram(0);
}

#pragma endregion

#pragma region common interfaces

void Shader::setBool(const char* name, bool value)
{
	// int location = this->getUniformLocation(name);
	// if (location == -1)
	// 	return;
	// auto pair = this->bools.find(location);
	// if (pair == this->bools.end()) 
	// {
	// 	this->bools.insert(std::pair<unsigned int,bool>(location,value));
	// 	return;
	// }
	// this->bools[location] = value;

	for (auto params = this->_bools.begin(); params != this->_bools.end(); params++) 
	{
		if (strcmp(params->first, name) == 0) 
		{
			params->second.value = value;
			return;
		}
	}

	ShaderBoolParams boolParam;
	boolParam.location = this->getUniformLocation(name);;
	boolParam.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_bools.insert(std::pair<const char*, ShaderBoolParams>(key, boolParam));
}
bool Shader::getBool(const char* name)
{
	int location = this->getUniformLocation(name);
	auto pair = this->bools.find(location);
	if (pair != this->bools.end())
		return this->bools[location];
	return false;
}

void Shader::setMat4(const char* name, glm::mat4 value) 
{
// 	int location = this->getUniformLocation(name);
// 	if (location == -1)
// 		return;
// 	auto pair = this->mat4Map.find(location);
// 	if (pair == this->mat4Map.end())
// 	{
// 		this->mat4Map.insert(std::pair<GLuint, glm::mat4>(location, value));
// 		return;
// 	}
// 	this->mat4Map[location] = value;

	for (auto params = this->_mat4s.begin(); params != this->_mat4s.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderMat4Params mat4Param;
	mat4Param.location = this->getUniformLocation(name);
	mat4Param.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_mat4s.insert(std::pair<const char*, ShaderMat4Params>(key, mat4Param));
}

void Shader::setVec2(const char* name, Vector2 value)
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->vec2Map.find(location);
	//if (pair == this->vec2Map.end())
	//{
	//	this->vec2Map.insert(std::pair<GLuint, Vector2>(location, value));
	//	return;
	//}
	//this->vec2Map[location] = value;

	for (auto params = this->_vec2s.begin(); params != this->_vec2s.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderVec2Params vec2Param;
	vec2Param.location = this->getUniformLocation(name);
	vec2Param.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_vec2s.insert(std::pair<const char*, ShaderVec2Params>(key, vec2Param));
}
Vector2 Shader::getVec2(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->vec2Map.find(location);
	if (pair != this->vec2Map.end())
		return this->vec2Map[location];
	return Vector2::zero;
}

void Shader::setVec3(const char* name, Vector3 value)
{
	// int location = this->getUniformLocation(name);
	// if (location == -1)
	// 	return;
	// auto pair = this->vec3Map.find(location);
	// if (pair == this->vec3Map.end())
	// {
	// 	this->vec3Map.insert(std::pair<GLuint,Vector3>(location,value));
	// 	return;
	// }
	// this->vec3Map[location] = value;

	for (auto params = this->_vec3s.begin(); params != this->_vec3s.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderVec3Params vec3Param;
	vec3Param.location = this->getUniformLocation(name);
	vec3Param.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_vec3s.insert(std::pair<const char*, ShaderVec3Params>(key, vec3Param));
}
Vector3 Shader::getVec3(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->vec3Map.find(location);
	if (pair != this->vec3Map.end())
		return this->vec3Map[location];
	return Vector3::zero;
}

void Shader::setVec4(const char* name, Vector4 value)
{
	/*int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->vec4Map.find(location);
	if (pair == this->vec4Map.end()) 
	{
		this->vec4Map.insert(std::pair<GLuint,Vector4>(location,value));
		return;
	}
	this->vec4Map[location] = value;*/

	for (auto params = this->_vec4s.begin(); params != this->_vec4s.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderVec4Params vec4Param;
	vec4Param.location = this->getUniformLocation(name);
	vec4Param.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_vec4s.insert(std::pair<const char*, ShaderVec4Params>(key, vec4Param));
}
Vector4 Shader::getVec4(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->vec4Map.find(location);
	if (pair != this->vec4Map.end())
		return this->vec4Map[location];
	return Vector4::zero;
}

void Shader::setInt(const char* name, GLint value)
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->ints.find(location);
	//if (pair == this->ints.end())
	//{
	//	this->ints.insert(std::pair<GLuint,GLuint>(location, value));
	//	return;
	//}
	//this->ints[location] = value;
	for (auto params = this->_ints.begin(); params != this->_ints.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderIntParams intParam;
	intParam.location = this->getUniformLocation(name);
	intParam.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_ints.insert(std::pair<const char*, ShaderIntParams>(key, intParam));
}
int Shader::getInt(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->ints.find(location);
	if (pair != this->ints.end())
		return this->ints[location];
	return 0;
}

void Shader::setFloat(const char* name, GLfloat value)
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->floats.find(location);
	//if (pair == this->floats.end())
	//{
	//	this->floats.insert(std::pair<GLuint,GLfloat>(location,value));
	//	return;
	//}
	//this->floats[location] = value;

	for (auto params = this->_ints.begin(); params != this->_ints.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderFloatParams floatParam;
	floatParam.location = this->getUniformLocation(name);
	floatParam.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_floats.insert(std::pair<const char*, ShaderFloatParams>(key, floatParam));
}
float Shader::getFloat(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->floats.find(location);
	if (pair != this->floats.end())
		return this->floats[location];
	return 0.0f;
}

void Shader::setColor(const char* name, Color color) 
{
	Colorf colorf(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	this->setColor(name, colorf);
}
Color Shader::getColor(const char* name) 
{
	Colorf colorf = this->GetColorf(name);
	return Color(colorf.r * 255, colorf.g * 255, colorf.b * 255, colorf.a * 255);
}

void Shader::setColor( const char* name, Colorf value)
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->colors.find(location);
	//if (pair == this->colors.end())
	//{
	//	this->colors.insert(std::pair<GLuint, Colorf>(location, color));
	//	return;
	//}
	//this->colors[location] = color;

	for (auto params = this->_colors.begin(); params != this->_colors.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = value;
			return;
		}
	}

	ShaderColorfParams colorParam;
	colorParam.location = this->getUniformLocation(name);
	colorParam.value = value;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_colors.insert(std::pair<const char*, ShaderColorfParams>(key, colorParam));
}
Colorf Shader::GetColorf(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->colors.find(location);
	if (pair != this->colors.end())
		return this->colors[location];
	return Colorf::white;
}

void Shader::setTexture(const char*name, GLuint value)
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->textures.find(location);
	//if (pair == this->textures.end())
	//{
	//	MaterialTexture mt;
	//	mt.texture = texture;
	//	this->textures.insert(std::pair<GLuint,MaterialTexture>(location,mt));
	//	return;
	//}
	//this->textures[location].texture = texture;

	for (auto params = this->_textures.begin(); params != this->_textures.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value.texture = value;
			return;
		}
	}

	ShaderTextureParams texParam;
	texParam.location = this->getUniformLocation(name);
	MaterialTexture mt;
	mt.texture = value;
	texParam.value = mt;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_textures.insert(std::pair<const char*, ShaderTextureParams>(key, texParam));
}
int Shader::getTexture(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
		return this->textures[location].texture;
	return -1;
}

void Shader::setTilling(const char* name, Vector2 tilling) 
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->textures.find(location);
	//if (pair != this->textures.end())
	//{
	//	MaterialTexture mt = this->textures[location];
	//	mt.tilling = tilling;
	//	this->textures[location] = mt;
	//}	
	for (auto params = this->_textures.begin(); params != this->_textures.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value.tilling = tilling;
			return;
		}
	} 
}
Vector2 Shader::getTilling(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
		return this->textures[location].tilling;
	return Vector2::zero;
}

void Shader::setOffset(const char* name, Vector2 offset) 
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->textures.find(location);
	//if (pair != this->textures.end())
	//{
	//	MaterialTexture mt = this->textures[location];
	//	mt.offset = offset;
	//	this->textures[location] = mt;
	//}

	for (auto params = this->_textures.begin(); params != this->_textures.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value.offset = offset;
			return;
		}
	}
}
Vector2 Shader::getOffset(const char* name) 
{
	int location = this->getUniformLocation(name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
		return this->textures[location].offset;
	return Vector2::zero;
}

void Shader::setCubemap(const char* name, Cubemap* cubemap)
{
	//int location = this->getUniformLocation(name);
	//if (location == -1)
	//	return;
	//auto pair = this->cubemaps.find(location);
	//if (pair == this->cubemaps.end())
	//{
	//	this->cubemaps[location] = cubemap;
	//	return;
	//}
	//this->cubemaps[location] = cubemap;
	for (auto params = this->_cubemaps.begin(); params != this->_cubemaps.end(); params++)
	{
		if (strcmp(params->first, name) == 0)
		{
			params->second.value = *cubemap;
			return;
		}
	}

	ShaderCubemapParams cubemapParam;
	cubemapParam.location = this->getUniformLocation(name);
	cubemapParam.value = *cubemap;
	char* key = new char[strlen(name)];
	strcpy_s(key, strlen(name) + 1, name);
	this->_cubemaps.insert(std::pair<const char*, ShaderCubemapParams>(key, cubemapParam));
}
int Shader::getCubemap(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->cubemaps.find(location);
	if (pair != this->cubemaps.end())
		return this->cubemaps[location]->cubemap;
	return -1;
}

#pragma endregion

void Shader::setShaderValues() 
{
// 	for (auto pair : this->bools) 
// 		glUniform1i(pair.first, pair.second);
	for (auto pair : this->_bools)
		glUniform1i(pair.second.location, pair.second.value);

// 	for (auto pair : this->ints)
// 		glUniform1i(pair.first, pair.second);
	for (auto pair : this->_ints)
		glUniform1i(pair.second.location, pair.second.value);

// 	for (auto pair : this->floats)
// 		glUniform1f(pair.first, pair.second);
	for (auto pair : this->_floats)
		glUniform1f(pair.second.location, pair.second.value);

// 	for (auto pair : this->colors)
// 	{
// 		Colorf color = pair.second;
// 		const float value[4] = { color.r ,color.g ,color.b,color.a };
// 		glUniform4fv(pair.first, 1, value);
// 	}
	for (auto pair : this->_colors)
	{
		Colorf color = pair.second.value;
		const float value[4] = { color.r ,color.g ,color.b,color.a };
		glUniform4fv(pair.second.location, 1, value);
	}

// 	for (auto pair : this->vec2Map)
// 	{
// 		Vector2 vec2 = pair.second;
// 		const float value[2] = { vec2.x,vec2.y};
// 		glUniform2fv(pair.first, 1, value);
// 	}
	for (auto pair : this->_vec2s)
	{
		Vector2 vec2 = pair.second.value;
		const float value[2] = { vec2.x,vec2.y };
		glUniform2fv(pair.second.location, 1, value);
	}

// 	for (auto pair : this->vec3Map)
// 	{
// 		Vector3 vec3 = pair.second;
// 		const float value[3] = {vec3.x,vec3.y,vec3.z};
// 		glUniform3fv(pair.first, 1, value);
// 	}
	for (auto vec3Param : this->_vec3s)
	{
		Vector3 vec3 = vec3Param.second.value;
		const float value[3] = { vec3.x,vec3.y,vec3.z };
		glUniform3fv(vec3Param.second.location, 1, value);
	}

// 	for (auto pair : this->vec4Map) 
// 	{
// 		Vector4 vec4 = pair.second;
// 		const float value[4] = {vec4.x,vec4.y,vec4.z,vec4.w};
// 		glUniform4fv(pair.first,1,value);
// 	}	
	for (auto pair : this->_vec4s)
	{
		Vector4 vec4 = pair.second.value;
		const float value[4] = { vec4.x,vec4.y,vec4.z ,vec4.z};
		glUniform4fv(pair.second.location, 1, value);
	}

// 	for (auto pair : this->mat4Map) 
// 	{
// 		glUniformMatrix4fv(pair.first, 1, GL_FALSE, glm::value_ptr(pair.second));
// 	}
	for (auto pair : this->_mat4s )
		glUniformMatrix4fv(pair.second.location, 1, GL_FALSE, glm::value_ptr(pair.second.value));

	unsigned int textureIndex = 0;
// 	for (std::pair<GLuint,MaterialTexture> pair : this->textures)
// 	{
// 		glUniform1i(pair.first, textureIndex);
// 		glActiveTexture(GL_TEXTURE0 + textureIndex++);
// 		glBindTexture(GL_TEXTURE_2D, pair.second.texture);
// 		GLuint tillingLocation = glGetUniformLocation(this->program, "MainTextureData.tilling");
// 		GLuint offsetLocation = glGetUniformLocation(this->program, "MainTextureData.offset");
// 		const float tilling[2] = {pair.second.tilling.x,pair.second.tilling.y};
// 		glUniform2fv(tillingLocation,1, tilling);
// 		const float offset[2] = { pair.second.offset.x,pair.second.offset.y };
// 		glUniform2fv(offsetLocation, 1, offset);
// 	}
	for (auto pair : this->_textures) 
	{
		glUniform1i(pair.second.location, textureIndex);
		glActiveTexture(GL_TEXTURE0 + textureIndex++);
		glBindTexture(GL_TEXTURE_2D, pair.second.value.texture);
		GLuint tillingLocation = glGetUniformLocation(this->program, "MainTextureData.tilling");
		GLuint offsetLocation = glGetUniformLocation(this->program, "MainTextureData.offset");
		const float tilling[2] = { pair.second.value.tilling.x,pair.second.value.tilling.y };
		glUniform2fv(tillingLocation, 1, tilling);
		const float offset[2] = { pair.second.value.offset.x,pair.second.value.offset.y };
		glUniform2fv(offsetLocation, 1, offset);
	}

// 	for (std::pair<GLuint, Cubemap*> pair : this->cubemaps) 
// 	{
// 		glUniform1i(pair.first, textureIndex);
// 		glActiveTexture(GL_TEXTURE0 + textureIndex++);
// 		glBindTexture(GL_TEXTURE_CUBE_MAP,pair.second->cubemap);
// 	}
	for (auto pair : this->_cubemaps)
	{
		glUniform1i(pair.second.location, textureIndex);
		glActiveTexture(GL_TEXTURE0 + textureIndex++);
		glBindTexture(GL_TEXTURE_CUBE_MAP, pair.second.value.cubemap);
	}
}

void Shader::setEngineEnvironment() 
{
	/*if (this->textures.size() <= 0)
		this->setTexture("MainTextureData.texture", TextureLoader::CreatePureWhiteTexture()->textureId);*/

	// camera pos
	GraphicProfiler::BeginSample("Set WorldSpaceCameraPos");
	this->setVec3(WorldSpaceCameraPos, Camera::main->transform->position);
	GraphicProfiler::EndSample();
	this->setVec3(CAMERA_POSITION, Camera::main->transform->position);

}

void Shader::setLighting() 
{
	if (!this->lightingIntialized) 
	{
		// ambient setting
		this->setColor(AMBIENT_COLOR, Environment::GetAmbientSetting().color);
		// shadow setting
		this->setInt(SHADOW_SAMPLELEVEL, Environment::GetShadowSetting().sample);

		bool hasMainTex = false;
		for (auto pair = this->_textures.begin(); pair != this->_textures.end(); pair++)
		{
			if (strcmp(pair->first, "MainTextureData.texture") == 0)
			{
				hasMainTex = true;
				break;
			}
		}
		if( !hasMainTex )  
			this->setTexture("MainTextureData.texture", TextureLoader::CreatePureWhiteTexture()->textureId);

		Light::ShaderSetting(*this);
		this->lightingIntialized = true;
	}

	for (Light* light : Light::lights) 
	{
		if (this->receiveShadow)
		{
			if (light->shadowType != Light::NoShadow)
			{
				if (nullptr != light->shadow)
				{
					unsigned int shadowmap = light->shadow->GetBuffer();
					this->setTexture(SHADOWMAP, shadowmap);
					this->setMat4("LightSpaceMatrix", light->lightSpaceMatrix);
				}
			}
		}
	}
}

void Shader::setTime()
{
	unsigned int timeLocation = this->getUniformLocation(_Time);
	if (timeLocation < 0)
		return;
	float time[4] = {shaderTimer.x,shaderTimer.y,shaderTimer.z,shaderTimer.w};
	glUniform4fv(timeLocation, 1, time);
}

#pragma region loading | caching | flash
char* Shader::loadShaderFile( const char*shaderFilePath )
{
	ifstream shaderFile;
	int length;
	shaderFile.open(shaderFilePath, ios::in|ios::binary);
	if (!shaderFile.good()) 
	{
		PRINT_ERROR("shader file %s is not exist.",shaderFilePath);
		return NULL;
	}
	shaderFile.seekg(0, ios::end);
	length = int(shaderFile.tellg());
	shaderFile.seekg(ios::beg);
	char* buffer = new char[length+1];
	shaderFile.read(buffer, length);
	buffer[length] = '\0';
	shaderFile.close();
	return buffer;
}

Shader* Shader::Load(const char* shaderName) 
{
	// todo : do not supports to load shader via shader name.
	return nullptr;
}
Shader* Shader::Load(const char* vertexShaderName, const char* fragmentShaderName, const char* geometryShaderName)
{
	const char* pathPrefix = "res/shader/";
	int length = (int)strlen(pathPrefix) + 1;

	int vsLength = length + (int)strlen(vertexShaderName);
	char* vs = (char*)malloc(vsLength*sizeof(char));
	memset(vs, 0, vsLength);
	strcat_s(vs, length + 1, pathPrefix);
	strcat_s(vs, vsLength, vertexShaderName);

	int fsLength = length + (int)strlen(fragmentShaderName);
	char* fs = (char*)malloc(fsLength * sizeof(char));
	memset(fs, 0, fsLength);
	strcat_s(fs, length + 1, pathPrefix);
	strcat_s(fs, fsLength, fragmentShaderName);

	char* gs = nullptr;
	if (nullptr != geometryShaderName)
	{
		int gsLength = length + (int)strlen(geometryShaderName);
		gs = (char*)malloc(gsLength * sizeof(char));
		memset(gs, 0, gsLength);
		strcat_s(gs, length + 1, pathPrefix);
		strcat_s(gs, gsLength, geometryShaderName);
	}

	Shader* shader = new Shader(vs, fs,gs);
	free(vs);
	free(fs);
	free(gs);

	shader->vertexShaderName = new char[strlen(vertexShaderName)];
	shader->fragmentShaderName = new char[strlen(fragmentShaderName)];
	strcpy_s(shader->vertexShaderName, strlen(vertexShaderName) + 1, vertexShaderName);
	strcpy_s(shader->fragmentShaderName, strlen(fragmentShaderName) + 1, fragmentShaderName);

	if (nullptr != geometryShaderName)
	{
		shader->geometryShaderName = new char[strlen(geometryShaderName)];
		strcpy_s(shader->geometryShaderName, strlen(geometryShaderName) + 1, geometryShaderName);
	}
	return shader;
}
void Shader::ForEach(std::function<void(Shader*)> func)
{
	for (Shader* shader : cachingShaders)
		func(shader);
}
void Shader::Caching(Shader* shader) 
{
	cachingShaders.push_back(shader);
}
void Shader::Flash(Shader* shader) 
{
	for (vector<Shader*>::iterator item = cachingShaders.begin(); item != cachingShaders.end();item++)
	{
		if (*item == shader)
		{
			cachingShaders.erase(item);
			return;
		}
	}
}

#pragma endregion
