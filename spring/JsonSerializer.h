#pragma once
#include "serializer.h"

namespace spring 
{
	class JsonSerializer : public Serializer
	{
	public:
		JsonSerializer();

		char* Serialize() override;
		void Deserialize() override;
	};
}