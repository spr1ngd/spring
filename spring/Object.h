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

		Object();
		virtual void Destroy();

		virtual const char* ToString();
		unsigned long GetInstanceID();
		static Object* Instantiate(Object obj);
	};
}