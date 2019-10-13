#pragma once
#include "json/json.h"
#include "ijsonserializer.h"

#pragma comment(lib,"lib_json.lib")

namespace spring 
{
	class JsonMapper
	{
	public:
		static const char* toJson(Json::Value jsonData);
		static Json::Value parseJson(const char* json);
	};
}