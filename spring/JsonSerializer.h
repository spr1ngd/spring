#pragma once
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "serializer.h"
#include "scene.h"

namespace spring 
{
	class JsonSerializer// : public Serializer
	{
	public:
		JsonSerializer();

		// char* Serialize() override;
		// void Deserialize() override;

		template<typename T>
		void Serialize(T* t);
		
		template<typename T>
		T* Deserialize();
	};
}