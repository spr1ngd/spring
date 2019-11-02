#include "object.h"
#include "console.h"
#include <iostream>

using namespace spring;

unsigned long Object::instanceCounts = 1000;

Object::Object()
{
	this->instanceId = GetInstanceID();
}

void Object::Destroy() 
{

}

const char* Object::ToString() 
{
	return this->name;
}

Object* Object::Instantiate(Object obj) 
{
	// todo 
	return nullptr;
}

unsigned long Object::GetInstanceID() 
{
	return Object::instanceCounts++;
}

//Json::Value Object::Serialize()
//{
//	Json::Value result;
//	return result;
//}
//
//void Object::Deserialize(Json::Value jsonData)
//{
//
//}