#include "gameobject.h"

using namespace spring;

GameObject::GameObject() 
{
	this->name = "GameObject";
}

GameObject::GameObject(const char* name) 
{
	this->name = name;
}