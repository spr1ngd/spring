#include "jsonserializer.h"
#include "springengine.h"
#include "scene.h"

using namespace spring;

Value* JsonSerializer::serializeVector3(Vector3 vec3,Document::AllocatorType& allocator) 
{
	Value* value = new Value(kObjectType);
	value->AddMember("x", vec3.x, allocator);
	value->AddMember("y", vec3.y, allocator);
	value->AddMember("z", vec3.z, allocator);
	return value;
}

Vector3 JsonSerializer::deserializeVector3(Value::MemberIterator vec3Member) 
{
	float x = vec3Member->value["x"].GetFloat();
	float y = vec3Member->value["y"].GetFloat();
	float z = vec3Member->value["z"].GetFloat();
	return Vector3(x,y,z);
}