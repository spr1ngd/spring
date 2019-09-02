#pragma once 

using namespace std;

namespace spring
{
	class Object
	{
	private:
		unsigned int instanceId;
	public:
		const char* name;
		Object();

	public:
		static Object* Instantiate(Object obj);
		static void Destroy();
	};
}


