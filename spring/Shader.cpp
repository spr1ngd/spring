#include <fstream>
#include "notimplementexception.h"
#include "console.h"
#include "shader.h"
#include "light.h"
#include "camera.h"
#include <string>
#include "texture.h"
#include "textureloader.h"

using namespace std;
using namespace spring;

std::vector<Shader*> Shader::cachingShaders;

Shader::Shader() 
{
	// todo : use default shader?
	Shader::Caching(this);
}

Shader::Shader( const char*vertexShader,const char*fragmentShader ) 
{
	GLuint vertex = this->compileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fragment = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	shaders.insert(pair<GLenum, GLuint>(GL_VERTEX_SHADER, vertex));
	shaders.insert(pair<GLenum, GLuint>(GL_FRAGMENT_SHADER, fragment));
	this->linkProgram();
	this->initializeLocation();
	Shader::Caching(this);
}

Shader::Shader(const char* vertexShader, const char* fragmentShader, const char* geometryShader) 
{
	GLuint vertex = this->compileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint geometry = this->compileShader(GL_GEOMETRY_SHADER, geometryShader);
	GLuint fragment = this->compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	shaders.insert(pair<GLenum, GLuint>(GL_VERTEX_SHADER, vertex));
	shaders.insert(pair<GLenum, GLuint>(GL_GEOMETRY_SHADER, geometry));
	shaders.insert(pair<GLenum, GLuint>(GL_FRAGMENT_SHADER, fragment));
	this->linkProgram();
	this->initializeLocation();
	Shader::Caching(this);
}

#pragma region shader program methods

void Shader::linkProgram()
{
	GLuint program = glCreateProgram();
	for (auto pair : shaders)
	{
		auto shader = pair.second;
		glAttachShader(program,shader);
	}
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

	GLuint nmLocation = glGetUniformLocation(this->program,MATRIX_NM);
	this->locations.insert(pair<CONST char*,GLuint>(MATRIX_NM,nmLocation));

	GLuint veretxLocation = glGetAttribLocation(this->program, VERTEX);
	this->locations.insert(pair<const char*, GLuint>(VERTEX, veretxLocation));

	GLuint normalLocation = glGetAttribLocation(this->program, NORMAL);
	this->locations.insert(pair<const char*, GLuint>(NORMAL, normalLocation));

	GLuint texcoordLocation = glGetAttribLocation(this->program, TEXCOORD);
	this->locations.insert(pair<const char*, GLuint>(TEXCOORD, texcoordLocation));

	GLuint colorLocation = glGetAttribLocation(this->program, COLOR);
	this->locations.insert(pair<const char*, GLuint>(COLOR, colorLocation));

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
	this->setLighting();
	this->setEngineEnvironment();
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
	delete source;
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
	length = int(shaderFile.tellg());
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
	GLuint location = glGetUniformLocation(this->program, name);
	throw new NotImplementException();
}

void Shader::setMat4(const char* name, glm::mat4 value) 
{
	GLuint location = glGetUniformLocation(this->program, name);
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
	GLuint location = glGetUniformLocation(this->program, name);
	auto pair = this->vec2Map.find(location);
	if (pair == this->vec2Map.end())
	{
		this->vec2Map.insert(std::pair<GLuint, Vector2>(location, value));
		return;
	}
	this->vec2Map[location] = value;
}

void Shader::setVec3(const char* name, Vector3 value)
{
	GLuint location = glGetUniformLocation(this->program, name);
	auto pair = this->vec3Map.find(location);
	if (pair == this->vec3Map.end())
	{
		this->vec3Map.insert(std::pair<GLuint,Vector3>(location,value));
		return;
	}
	this->vec3Map[location] = value;
}

void Shader::setVec4(const char* name, Vector4 value)
{
	GLuint location = glGetUniformLocation(this->program, name);
	auto pair = this->vec4Map.find(location);
	if (pair == this->vec4Map.end()) 
	{
		this->vec4Map.insert(std::pair<GLuint,Vector4>(location,value));
		return;
	}
	this->vec4Map[location] = value;
}

void Shader::setInt(const char* name, GLint value)
{
	GLuint location = glGetUniformLocation(this->program, name);
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
	GLuint location = glGetUniformLocation(this->program, name);
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
	GLuint location = glGetUniformLocation(this->program, name);
	auto pair = this->colors.find(location);
	if (pair == this->colors.end())
	{
		this->colors.insert(std::pair<GLuint,Color>(location, color));
		return;
	}
	this->colors[location] = color;
}

void Shader::setTexture(const char*name, GLuint texture)
{
	GLuint location = glGetUniformLocation(this->program, name);
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

void Shader::setTilling(const char* name, Vector2 tilling) 
{
	GLuint location = glGetUniformLocation(this->program,name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
	{
		MaterialTexture mt = this->textures[location];
		mt.tilling = tilling;
		this->textures[location] = mt;
	}
}

void Shader::setOffset(const char* name, Vector2 offset) 
{
	GLuint location = glGetUniformLocation(this->program, name);
	auto pair = this->textures.find(location);
	if (pair != this->textures.end())
	{
		MaterialTexture mt = this->textures[location];
		mt.offset = offset;
		this->textures[location] = mt;
	}
}

void Shader::setCubemap(const char* name, Cubemap cubemap)
{
	GLuint location = glGetUniformLocation(this->program,name);
	auto pair = this->cubemaps.find(location);
	if (pair == this->cubemaps.end())
	{
		this->cubemaps[location] = cubemap;
		return;
	}
	this->cubemaps[location] = cubemap;
}

void Shader::setShaderValues() 
{
	for (auto pair : this->ints)
	{
		glUniform1i(pair.first, pair.second);
	}

	for (auto pair : this->floats)
	{
		glUniform1f(pair.first, pair.second);
	}

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

	for (std::pair<GLuint, Cubemap> pair : this->cubemaps) 
	{
		glUniform1i(pair.first, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP,pair.second.cubemap);
	}
}

void Shader::setEngineEnvironment() 
{
	if( this->textures.size() <= 0 )
		this->setTexture("MainTextureData.texture", TextureLoader::GenPureWhiteTexture()->textureId);

	// ambient setting
	this->setColor(AMBIENT_COLOR,Environment::ambient.color);

	// shadow setting
	this->setInt(SHADOW_SAMPLELEVEL,Environment::shadow.sample);
}

void Shader::setLighting() 
{
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
			std::string intensityStr = arrayName + '[' + to_string(directionalLightCount) + "]." + intensity;
			std::string positionStr = arrayName + '[' + to_string(directionalLightCount) + "]." + position;
			std::string colorStr = arrayName + '[' + to_string(directionalLightCount) + "]." + color;
			this->setFloat(intensityStr.c_str(), light->intensity);
			this->setVec3(positionStr.c_str(), light->transform->position);
			this->setColor(colorStr.c_str(), light->color);
			directionalLightCount++;
		}
		else if (light->type == Light::Type::Point)
		{
			string arrayName = "pointLights";
			std::string intensityStr = arrayName + '[' + to_string(pointLightCount) + "]." + intensity;
			std::string positionStr = arrayName + '[' + to_string(pointLightCount) + "]." + position;
			std::string colorStr = arrayName + '[' + to_string(pointLightCount) + "]." + color;
			std::string rangeStr = arrayName + '[' + to_string(pointLightCount) + "]." + range;
			std::string constantStr = arrayName + '[' + to_string(pointLightCount) + "]." + constant;
			std::string linearStr = arrayName + '[' + to_string(pointLightCount) + "]." + linear;
			std::string quadraticStr = arrayName + '[' + to_string(pointLightCount) + "]." + quadratic;
			this->setFloat(intensityStr.c_str(), light->intensity);
			this->setVec3(positionStr.c_str(), light->transform->position);
			this->setColor(colorStr.c_str(), light->color);
			this->setFloat(rangeStr.c_str(), light->range);
			this->setFloat(constantStr.c_str(), light->constant);
			this->setFloat(linearStr.c_str(), light->linear);
			this->setFloat(quadraticStr.c_str(), light->quadratic);
			pointLightCount++;
		}
		else if (light->type == Light::Type::Spot)
		{
			string arrayName = "spotLights";
			std::string intensityStr = arrayName + '[' + to_string(spotLightCount) + "]." + intensity;
			std::string positionStr = arrayName + '[' + to_string(spotLightCount) + "]." + position;
			std::string directionStr = arrayName + '[' + to_string(spotLightCount) + "]." + direction;
			std::string colorStr = arrayName + '[' + to_string(spotLightCount) + "]." + color;
			std::string rangeStr = arrayName + '[' + to_string(spotLightCount) + "]." + range;
			std::string constantStr = arrayName + '[' + to_string(spotLightCount) + "]." + constant;
			std::string linearStr = arrayName + '[' + to_string(spotLightCount) + "]." + linear;
			std::string quadraticStr = arrayName + '[' + to_string(spotLightCount) + "]." + quadratic;
			std::string cutoffStr = arrayName + '[' + to_string(spotLightCount) + "]." + cutoff;
			std::string outerCutoffStr = arrayName + '[' + to_string(spotLightCount) + "]." + outerCutoff;

			this->setFloat(intensityStr.c_str(), light->intensity);
			this->setVec3(positionStr.c_str(), light->transform->position);
			this->setColor(colorStr.c_str(), light->color);
			this->setFloat(rangeStr.c_str(), light->range);
			this->setFloat(constantStr.c_str(), light->constant);
			this->setFloat(linearStr.c_str(), light->linear);
			this->setFloat(quadraticStr.c_str(), light->quadratic);
			this->setFloat(cutoffStr.c_str(), glm::cos(glm::radians(light->spotAngle / 2.0f)));
			this->setFloat(outerCutoffStr.c_str(), glm::cos(glm::radians(light->outterAngle / 2.0f)));
			this->setVec3(directionStr.c_str(), light->transform->GetEulerangle());
			spotLightCount++;
		}
		else
		{

		}
		this->setVec3(CAMERA_POSITION, Camera::main->transform->position);

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

#pragma region caching | flash

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
