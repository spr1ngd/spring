#pragma once 

using namespace std;

namespace spring
{
	class Object
	{
	protected:
		unsigned long instanceId;
	public:
		const char* name;
		Object();
		const char* ToString();
	public:
		unsigned long GetInstanceID();
		static Object* Instantiate(Object obj);
		static void Destroy();
	};
}


