#pragma once 
#include "jsonmapper.h"

using namespace std;

namespace spring 
{
	class Object : public IJsonSerializer
	{
		friend class JsonMapper;
	private:
		static unsigned long instanceCounts;
	protected:
		unsigned long instanceId;
		Json::Value Serialize() override;
		void Deserialize(Json::Value jsonData) override;
	public:
		const char* name;

		Object();
		const char* ToString();
		unsigned long GetInstanceID();
		static Object* Instantiate(Object obj);
		static void Destroy();
	};
}