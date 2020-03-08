#pragma once
#include "scene.h"

namespace spring 
{
	class SceneSerializer 
	{
	public:
		enum SerializeFormat 
		{
			JSON,
			BIN
		};

		SerializeFormat serializeFormat = SerializeFormat::JSON;
		Scene& scene;
		const char* scenePath;

		SceneSerializer(Scene& scene);
		void Serialize();
		void Deserialize();
	};
}