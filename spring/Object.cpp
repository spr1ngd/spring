#include "Object.h"

using namespace spring;

Object::Object()
{

}

const char* Object::ToString() 
{
	return this->name;
}

Object* Object::Instantiate(Object obj) 
{
	return nullptr;
}

void Object::Destroy()
{

}

unsigned long Object::GetInstanceID() 
{
	return 0;
}
