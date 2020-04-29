#include "gameobject.h"
#include "node.h"
#include "scene.h"
#include "console.h"

using namespace std;
using namespace spring;

std::vector<GameObject*> GameObject::gameobjects;

GameObject::GameObject() 
{
	this->name = "GameObject";
	this->transform = new Transform();
	this->transform->gameobject = this;
	AddGameObject(this);
}

GameObject::GameObject(const char* name) 
{
	this->name = name;
	this->transform = new Transform();
	this->transform->gameobject = this;
	AddGameObject(this);
}

GameObject::~GameObject()
{
	// destroy from current scene or current parent.
	RemoveGameObject(this);
	// destroy all additional nodes
	for (Node* node : nodes)
		node->Destroy();
	// destroy all children nodes
	for (GameObject* child : children)
		child->Destroy();
	PRINT_WARNING("Gameobject [%s] has been destroy from memory.",this->name);
}

void GameObject::Destroy() 
{
	delete this;
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
			if( nullptr == gameobject->parent )
				Scene::current->RemoveGameObject(gameobject);
			else
			{
				for (auto child = gameobject->children.begin(); child != gameobject->children.end(); child++) 
				{
					GameObject* childPtr = *child;
					if (childPtr == gameobject)
					{
						gameobject->children.erase(child);
						gameobject->parent = nullptr;
						break;
					}
				}
			}
			return;
		}
	}
}

#pragma endregion
