#pragma once 

using namespace std;

namespace spring
{
	class Object
	{
	private:
		static unsigned long instanceCounts;
	protected:
		unsigned long instanceId;
	public:
		const char* name;
		const char* ToString();

		Object();
		unsigned long GetInstanceID();
		static Object* Instantiate(Object obj);
		static void Destroy();
	};
}


