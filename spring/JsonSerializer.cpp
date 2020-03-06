#include "jsonserializer.h"
#include "springengine.h"

using namespace spring;

JsonSerializer::JsonSerializer()// : Serializer()
{

}

//char* JsonSerializer::Serialize() 
//{
//	return nullptr;
//} 

template<typename T>
void JsonSerializer::Serialize(T* t) 
{
	// const char* typeName = typeid(t).name();
	// const char* vec3Name = typeid(Vector3).name();
	// const char* sceneName = typeid(Scene).name();
	// 
	// Console::Error("%s,%s,%s", typeName, vec3Name, sceneName);
}
template<typename T>
T* JsonSerializer::Deserialize() 
{
	return nullptr;
}