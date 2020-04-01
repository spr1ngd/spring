#include "gameobject.h"
#include "scene.h"

using namespace std;
using namespace spring;

std::vector<GameObject*> GameObject::gameobjects;

GameObject::GameObject() 
{
	this->name = "GameObject";
	AddGameObject(this);
}

GameObject::GameObject(const char* name) 
{
	this->name = name;
	AddGameObject(this);
}

#pragma region static methods

void GameObject::AddGameObject(GameObject* gameobject) 
{
	for (auto go = gameobjects.begin();go != gameobjects.end();go++)
	{
		GameObject* goPtr = *go;
		if (goPtr == gameobject)
		{
			PRINT_ERROR("can not cache the same gameobject %s",gameobject->name);
			return;
		}
	}
	gameobjects.push_back(gameobject);
	Scene::current->AddGameObject(gameobject);
}

void GameObject::RemoveGameObject(GameObject* gameobject) 
{
	for (auto go = gameobjects.begin(); go != gameobjects.end(); go++) 
	{
		GameObject* goPtr = *go;
		if (goPtr == gameobject)
		{
			gameobjects.erase(go);
			Scene::current->RemoveGameObject(gameobject);
			return;
		}
	}
}

#pragma endregion
