#pragma once
#include <map>
#include "glm/glm.hpp"
#include "node.h"
#include "color.h"
#include "colorf.h"
#include "transform.h"
#include "vector3.h"
#include "vector4.h"
#include "material.h"
#include "framebuffer.h"
#include "layer.h"

//string intensity = "intensity";
//string color = "color";
//string position = "position";
//string range = "range";
//string constant = "constant";
//string linear = "linear";
//string quadratic = "quadratic";
//string direction = "direction";
//string cutoff = "cutoff";
//string outerCutoff = "outerCutoff";

#define _LIGHT_INTENSITY "intensity"
#define _LIGHT_COLOR "color"
#define _LIGHT_POSITION "position"
#define _LIGHT_RANGE "range"
#define _LIGHT_CONSTANT "constant"
#define _LIGHT_LINEAR "linear"
#define _LIGHT_QUADRATIC "quadratic"
#define _LIGHT_DIRECTION "direction"
#define _LIGHT_CUTOFF "cutoff"
#define _LIGHT_OUTERCUTOFF "outerCutoff"

namespace spring 
{
	class Shader;
	struct ShadowMappingParams
	{
		unsigned int shadowMapSize = 1024;
		float size = 10.0f;
		float zNear = -1.0f;
		float zFar = 50.0f;
		glm::mat4 projection;
	};
	struct LightParams 
	{
		Colorf color = Colorf::white;
		float intensity = 1.0f;
		// only work in spot and point mode
		float range = 10.0f;
		float constant = 1.0f;
		float linear = 0.09f;
		float quadratic = 0.032f;
		// only work in spot light mode
		float spotAngle = 25.0f;
		float outterAngle = 70.0f;
	};
	class Light : public Node
	{
	public:
		enum Type 
		{
			Directional,
			Spot,
			Point,
			Area
		};
		enum RenderMode
		{
			Auto,
			Pixel,
			Vertex
		};
		enum ShadowType 
		{
			NoShadow,
			HardShadow,
			SoftShadow
		};

	private:
		static Material* depthMaterial;
		static Material* tMaterial;

		bool lightParametersChangedInThisFrame = true;
		unsigned int lightId = 0;

	public:
		static std::vector<Light*> lights;
		static Light* main;

		Light::RenderMode renderMode = Light::RenderMode::Auto;
		Light::Type type = Light::Type::Directional;
		Colorf color = Colorf::white;
		LightParams setting;

		//lighting mapping setting
		glm::mat4 lightSpaceMatrix;
		ShadowType shadowType = ShadowType::HardShadow;
		ShadowMappingParams shadowMapping;
		FrameBuffer* shadow;
		FrameBuffer* tbuffer; 
		LayerMask layers;

	public:
		Light();
		~Light();

		void SetShadowMappingParams(unsigned int shadowMapSize, float size, float zNear, float zFar)
		{
			this->shadowMapping.shadowMapSize = shadowMapSize;
			this->shadowMapping.size = size;
			this->shadowMapping.zNear = zNear;
			this->shadowMapping.zFar = zFar;
			this->shadowMapping.projection = glm::ortho(-size, size, -size, size, zNear, zFar);
		}
		void SetLightParams(float intensity , Colorf lightColor) 
		{
			this->setting.intensity = intensity;
			this->setting.color = lightColor;
			this->ResetShaderLightParams();
		}
		void SetLightParams(float intensity,float range,float constant,float linear,float quadratic)
		{
			this->setting.intensity = intensity;
			this->setting.range = range;
			this->setting.constant = constant;
			this->setting.linear = linear;
			this->setting.quadratic = quadratic;
			this->ResetShaderLightParams();
		}
		void SetLightParams(float intensity, float range, float constant, float linear, float quadratic,float spotAngle,float outerAngle)
		{
			this->setting.intensity = intensity;
			this->setting.range = range;
			this->setting.constant = constant;
			this->setting.linear = linear;
			this->setting.quadratic = quadratic;
			this->setting.spotAngle = spotAngle;
			this->setting.outterAngle = outerAngle;
			this->ResetShaderLightParams();
		}

		void ResetShaderLightParams();// for each shader instance , set light params to shader.
		void SetDirectionalLightParams(Shader* shader);
		void SetSpotLightParams(Shader* shader);
		void SetPointLightParams(Shader* shader);
		void SetAreaLightParams(Shader* shader);

		static void ShaderSetting(Shader& shader);
		static void CastShadow();
		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("Light");
			return *this->typeInfo;
		}
	};
}