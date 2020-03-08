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

using namespace std;
using namespace spring;

std::vector<Shader*> Shader::cachingShaders;
Vector4 Shader::shaderTimer;
Shader* Shader::error;

Shader::Shader()
{
	Shader::Caching(this);
}

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
	bool success = true;
	unsigned int vertex_shader, fragment_shader;
	success &= this->compile(GL_VERTEX_SHADER, vertexShader, vertex_shader);
	success &= this->compile(GL_FRAGMENT_SHADER, fragmentShader, fragment_shader);
	success &= this->link(vertex_shader, fragment_shader);
	if (success == false)
	{
		Console::Error("shader error , replaced by default error shader.");
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

Shader::Shader(const char* vertexShader, const char* fragmentShader, const char* geometryShader)
{
	bool success = true;
	unsigned int vertex_shader, fragment_shader, geometry_shader;
	success &= this->compile(GL_VERTEX_SHADER, vertexShader, vertex_shader);
	success &= this->compile(GL_GEOMETRY_SHADER, geometryShader, geometry_shader);
	success &= this->compile(GL_FRAGMENT_SHADER, fragmentShader, fragment_shader);
	success &= this->link(vertex_shader, fragment_shader, geometry_shader);
	if (success == false)
	{
		Console::Error("shader error , replaced by default error shader.");
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
		Console::Error(infoLog);
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
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, logInfo);
		Console::Error(logInfo);
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
		Console::Error(logInfo);
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
	auto pair = this->locations.find(name);
	if (pair != this->locations.end())
		return this->locations[name];
	unsigned int location = glGetUniformLocation(this->program,name);
	if (location == -1) 
		return location;
	this->locations.insert(std::pair<const char*, unsigned int>(name, location));
	return location;
}

GLuint Shader::getLocation(const char* name)
{
	auto pair = this->locations.find(name);
	if (pair == this->locations.end())
		return -1;
	return pair->second;
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
	this->setLighting();
	this->setEngineEnvironment();
	this->setShaderValues();
	this->setTime();
}

void Shader::disuse() 
{
	glUseProgram(0);
}

#pragma endregion

#pragma region common interfaces

void Shader::setBool(const char* name, bool value)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->bools.find(location);
	if (pair == this->bools.end()) 
	{
		this->bools.insert(std::pair<unsigned int,bool>(location,value));
		return;
	}
	this->bools[location] = value;
}
bool Shader::getBool(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->bools.find(location);
	if (pair != this->bools.end())
		return this->bools[location];
	return false;
}

void Shader::setMat4(const char* name, glm::mat4 value) 
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->mat4Map.find(location);
	if (pair == this->mat4Map.end())
	{
		this->mat4Map.insert(std::pair<GLuint, glm::mat4>(location, value));
		return;
	}
	this->mat4Map[location] = value;
}

void Shader::setVec2(const char* name, Vector2 value)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->vec2Map.find(location);
	if (pair == this->vec2Map.end())
	{
		this->vec2Map.insert(std::pair<GLuint, Vector2>(location, value));
		return;
	}
	this->vec2Map[location] = value;
}
Vector2 Shader::getVec2(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->vec2Map.find(location);
	if (pair != this->vec2Map.end())
		return this->vec2Map[location];
	return Vector2::zero;
}

void Shader::setVec3(const char* name, Vector3 value)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->vec3Map.find(location);
	if (pair == this->vec3Map.end())
	{
		this->vec3Map.insert(std::pair<GLuint,Vector3>(location,value));
		return;
	}
	this->vec3Map[location] = value;
}
Vector3 Shader::getVec3(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->vec3Map.find(location);
	if (pair != this->vec3Map.end())
		return this->vec3Map[location];
	return Vector3::zero;
}

void Shader::setVec4(const char* name, Vector4 value)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->vec4Map.find(location);
	if (pair == this->vec4Map.end()) 
	{
		this->vec4Map.insert(std::pair<GLuint,Vector4>(location,value));
		return;
	}
	this->vec4Map[location] = value;
}
Vector4 Shader::getVec4(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->vec4Map.find(location);
	if (pair != this->vec4Map.end())
		return this->vec4Map[location];
	return Vector4::zero;
}

void Shader::setInt(const char* name, GLint value)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->ints.find(location);
	if (pair == this->ints.end())
	{
		this->ints.insert(std::pair<GLuint,GLuint>(location, value));
		return;
	}
	this->ints[location] = value;
}
int Shader::getInt(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->ints.find(location);
	if (pair != this->ints.end())
		return this->ints[location];
	return 0;
}

void Shader::setFloat(const char* name, GLfloat value)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->floats.find(location);
	if (pair == this->floats.end())
	{
		this->floats.insert(std::pair<GLuint,GLfloat>(location,value));
		return;
	}
	this->floats[location] = value;
}
float Shader::getFloat(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
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

void Shader::setColor( const char* name, Colorf color )   
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->colors.find(location);
	if (pair == this->colors.end())
	{
		this->colors.insert(std::pair<GLuint, Colorf>(location, color));
		return;
	}
	this->colors[location] = color;
}
Colorf Shader::GetColorf(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->colors.find(location);
	if (pair != this->colors.end())
		return this->colors[location];
	return Colorf::white;
}

void Shader::setTexture(const char*name, GLuint texture)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->textures.find(location);
	if (pair == this->textures.end())
	{
		MaterialTexture mt;
		mt.texture = texture;
		this->textures.insert(std::pair<GLuint,MaterialTexture>(location,mt));
		return;
	}
	this->textures[location].texture = texture;
}
int Shader::getTexture(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
		return this->textures[location].texture;
	return -1;
}

void Shader::setTilling(const char* name, Vector2 tilling) 
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
	{
		MaterialTexture mt = this->textures[location];
		mt.tilling = tilling;
		this->textures[location] = mt;
	}
}
Vector2 Shader::getTilling(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
		return this->textures[location].tilling;
	return Vector2::zero;
}

void Shader::setOffset(const char* name, Vector2 offset) 
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
	{
		MaterialTexture mt = this->textures[location];
		mt.offset = offset;
		this->textures[location] = mt;
	}
}
Vector2 Shader::getOffset(const char* name) 
{
	unsigned int location = this->getUniformLocation(name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
		return this->textures[location].offset;
	return Vector2::zero;
}

void Shader::setCubemap(const char* name, Cubemap* cubemap)
{
	unsigned int location = this->getUniformLocation(name);
	if (location == -1)
		return;
	auto pair = this->cubemaps.find(location);
	if (pair == this->cubemaps.end())
	{
		this->cubemaps[location] = cubemap;
		return;
	}
	this->cubemaps[location] = cubemap;
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
	for (auto pair : this->bools) 
		glUniform1i(pair.first, pair.second);

	for (auto pair : this->ints)
		glUniform1i(pair.first, pair.second);

	for (auto pair : this->floats)
		glUniform1f(pair.first, pair.second);

	for (auto pair : this->colors)
	{
		Colorf color = pair.second;
		const float value[4] = { color.r ,color.g ,color.b,color.a };
		glUniform4fv(pair.first, 1, value);
	}

	for (auto pair : this->vec2Map)
	{
		Vector2 vec2 = pair.second;
		const float value[2] = { vec2.x,vec2.y};
		glUniform2fv(pair.first, 1, value);
	}

	for (auto pair : this->vec3Map)
	{
		Vector3 vec3 = pair.second;
		const float value[3] = {vec3.x,vec3.y,vec3.z};
		glUniform3fv(pair.first, 1, value);
	}

	for (auto pair : this->vec4Map) 
	{
		Vector4 vec4 = pair.second;
		const float value[4] = {vec4.x,vec4.y,vec4.z,vec4.w};
		glUniform4fv(pair.first,1,value);
	}

	for (auto pair : this->mat4Map) 
	{
		glUniformMatrix4fv(pair.first, 1, GL_FALSE, glm::value_ptr(pair.second));
	}

	unsigned int textureIndex = 0;
	for (std::pair<GLuint,MaterialTexture> pair : this->textures)
	{
		glUniform1i(pair.first, textureIndex);
		glActiveTexture(GL_TEXTURE0 + textureIndex++);
		glBindTexture(GL_TEXTURE_2D, pair.second.texture);
		GLuint tillingLocation = glGetUniformLocation(this->program, "MainTextureData.tilling");
		GLuint offsetLocation = glGetUniformLocation(this->program, "MainTextureData.offset");
		const float tilling[2] = {pair.second.tilling.x,pair.second.tilling.y};
		glUniform2fv(tillingLocation,1, tilling);
		const float offset[2] = { pair.second.offset.x,pair.second.offset.y };
		glUniform2fv(offsetLocation, 1, offset);
	}

	for (std::pair<GLuint, Cubemap*> pair : this->cubemaps) 
	{
		glUniform1i(pair.first, textureIndex);
		glActiveTexture(GL_TEXTURE0 + textureIndex++);
		glBindTexture(GL_TEXTURE_CUBE_MAP,pair.second->cubemap);
	}
}

void Shader::setEngineEnvironment() 
{
	if( this->textures.size() <= 0 )
		this->setTexture("MainTextureData.texture", TextureLoader::CreatePureWhiteTexture()->textureId);

	// ambient setting
	this->setColor(AMBIENT_COLOR,Environment::ambient.color);

	// shadow setting
	this->setInt(SHADOW_SAMPLELEVEL,Environment::shadow.sample);
}

void Shader::setLighting() 
{
	if (!this->enableLighting)
		return;
	string intensity = "intensity";
	string color = "color";
	string position = "position";
	string range = "range";
	string constant = "constant";
	string linear = "linear";
	string quadratic = "quadratic";
	string direction = "direction";
	string cutoff = "cutoff";
	string outerCutoff = "outerCutoff";

	int directionalLightCount = 0;
	int pointLightCount = 0;
	int spotLightCount = 0;
	for (auto light : Light::lights)
	{
		if (light->type == Light::Type::Directional)
		{
			string arrayName = "dirLights";
			char* intensityName = spring::misc::string2c((arrayName + '[' + to_string(directionalLightCount) + "]." + intensity));
			char* positionName = spring::misc::string2c((arrayName + '[' + to_string(directionalLightCount) + "]." + position));
			char* colorName = spring::misc::string2c((arrayName + '[' + to_string(directionalLightCount) + "]." + color));
			this->setFloat(intensityName, light->intensity);
			this->setVec3(positionName, light->transform->position);
			this->setColor(colorName, light->color);
			directionalLightCount++;
		}
		else if (light->type == Light::Type::Point)
		{
			string arrayName = "pointLights";
			auto intensityStr = spring::misc::string2c((arrayName + '[' + to_string(pointLightCount) + "]." + intensity));
			auto positionStr = spring::misc::string2c((arrayName + '[' + to_string(pointLightCount) + "]." + position));
			auto colorStr = spring::misc::string2c((arrayName + '[' + to_string(pointLightCount) + "]." + color));
			auto rangeStr = spring::misc::string2c((arrayName + '[' + to_string(pointLightCount) + "]." + range));
			auto constantStr = spring::misc::string2c((arrayName + '[' + to_string(pointLightCount) + "]." + constant));
			auto linearStr = spring::misc::string2c(arrayName + '[' + to_string(pointLightCount) + "]." + linear);
			auto quadraticStr = spring::misc::string2c(arrayName + '[' + to_string(pointLightCount) + "]." + quadratic);
			this->setFloat(intensityStr, light->intensity);
			this->setVec3(positionStr, light->transform->position);
			this->setColor(colorStr, light->color);
			this->setFloat(rangeStr, light->range);
			this->setFloat(constantStr, light->constant);
			this->setFloat(linearStr, light->linear);
			this->setFloat(quadraticStr, light->quadratic);
			pointLightCount++;
		}
		else if (light->type == Light::Type::Spot)
		{
			string arrayName = "spotLights";
			char* intensityStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + intensity);
			char* positionStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + position);
			char* directionStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + direction);
			char* colorStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + color);
			char* rangeStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + range);
			char* constantStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + constant);
			char* linearStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + linear);
			char* quadraticStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + quadratic);
			char* cutoffStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + cutoff);
			char* outerCutoffStr = spring::misc::string2c(arrayName + '[' + to_string(spotLightCount) + "]." + outerCutoff);
			this->setFloat(intensityStr, light->intensity);
			this->setVec3(positionStr, light->transform->position);
			this->setColor(colorStr, light->color);
			this->setFloat(rangeStr, light->range);
			this->setFloat(constantStr, light->constant);
			this->setFloat(linearStr, light->linear);
			this->setFloat(quadraticStr, light->quadratic);
			this->setFloat(cutoffStr, glm::cos(glm::radians(light->spotAngle / 2.0f)));
			this->setFloat(outerCutoffStr, glm::cos(glm::radians(light->outterAngle / 2.0f)));
			this->setVec3(directionStr, light->transform->GetEulerangle());
			spotLightCount++;
		}
		else
		{

		}
		this->setVec3(CAMERA_POSITION, Camera::main->transform->position);

		if (this->receiveShadow)
		{
			// add light shadow map for shader program
			if (light->shadowType != Light::NoShadow)
			{
				if (nullptr != light->shadow)
				{
					GLuint shadowmap = light->shadow->buffer;
					this->setTexture(SHADOWMAP, shadowmap);
					// set light space matrix.
					this->setMat4("LightSpaceMatrix", light->lightSpaceMatrix);
				}
				else
				{
					Console::ErrorFormat("[spring engine] Shader : light does not have shadow map.");
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

Shader* Shader::Load(const char* vertexShaderName, const char* fragmentShaderName)
{
	const char* pathPrefix = "res/shader/";
	int length = (int)strlen(pathPrefix) + 1;
	int vsLength = length + (int)strlen(vertexShaderName);
	int fsLength = length + (int)strlen(fragmentShaderName);
	char* vs = (char*)malloc(vsLength*sizeof(char));
	memset(vs, 0, vsLength);
	strcat_s(vs, length + 1, pathPrefix);
	strcat_s(vs, vsLength, vertexShaderName);

	char* fs = (char*)malloc(fsLength * sizeof(char));
	memset(fs, 0, fsLength);
	strcat_s(fs, length + 1, pathPrefix);
	strcat_s(fs, fsLength, fragmentShaderName);

	Shader* shader = new Shader(vs, fs);
	free(vs);
	free(fs);

	shader->vertexShaderName = new char[strlen(vertexShaderName)];
	shader->fragmentShaderName = new char[strlen(fragmentShaderName)];
	strcpy_s(shader->vertexShaderName, strlen(vertexShaderName) + 1, vertexShaderName);
	strcpy_s(shader->fragmentShaderName, strlen(fragmentShaderName) + 1, fragmentShaderName);
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
	length = int(shaderFile.tellg());
	shaderFile.seekg(ios::beg);
	char* buffer = new char[length+1];
	shaderFile.read(buffer, length);
	buffer[length] = '\0';
	shaderFile.close();
	return buffer;
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
