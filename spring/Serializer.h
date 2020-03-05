#pragma once
#include "jsonserializer.h"

namespace spring 
{
	class Serializer 
	{
	public:
		Serializer();

		virtual char* Serialize() = 0;
		virtual void Deserialize() = 0;
	};
}