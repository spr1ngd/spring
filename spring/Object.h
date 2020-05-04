#pragma once 

using namespace std;

namespace spring 
{
	class TypeInfo
	{
	public:
		const char* typeName;

		TypeInfo(const char* typeName)
		{
			this->typeName = typeName;
		}
	};

	class Object
	{ 
	private:
		static unsigned long instanceCounts;
	protected:
		unsigned long instanceId;
		TypeInfo* typeInfo;
	public:
		const char* name;

		Object();
		virtual ~Object();
		virtual void Destroy();

		virtual const char* ToString();
		unsigned long GetInstanceID();
		static Object* Instantiate(Object obj);

		virtual TypeInfo GetTypeInfo()
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("Object");
			return *this->typeInfo;
		}
	};
}