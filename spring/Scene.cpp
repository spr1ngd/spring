#include "scene.h"
#include "sceneserializer.h"

using namespace spring;

std::map<const char*, Scene*> Scene::scenes;
Scene* Scene::current;

Scene::Scene(const char* name) 
{
	this->name = name;
}

#pragma region manage methods

void Scene::Load(const char* sceneName)
{
	// todo : restore scene data to actual scene object
}

void Scene::Unload(const char* sceneName)
{
	// todo : remove all scene objects
}

Scene* Scene::ReadScene(const char* scenePath)
{
	// todo : deserialize scene file to scene object.
	return nullptr;
}

void Scene::SaveScene(const char* scenePath, Scene* scene)
{
	SceneSerializer sceneSerializer(scene, scenePath);
	sceneSerializer.Serialize();
}

void Scene::AddScene(Scene* scene) 
{
	auto item = scenes.find(scene->name);
	if (item != scenes.end())
		return;
	scenes[scene->name] = scene;
	Console::LogFormat("[Scene] : add new scene %s.",scene->name);
}

void Scene::RemoveScene(Scene* scene) 
{
	for (auto item = scenes.begin(); item != scenes.end(); item++)
	{
		if (item->first == scene->name) 
		{
			scenes.erase(item);
			Console::LogFormat("[Scene] : remove scene %s",scene->name);
			return;
		}
	}
}

#pragma endregion

#pragma region scene interfaces

void Scene::AddNode(Node* node) 
{
	auto item = this->nodes.find(node->name);
	if (item != this->nodes.end())
	{
		Console::ErrorFormat("[Scene] : can not add the same name node in [%s] scene.",this->name);
		return;
	}
	this->nodes[node->name] = node;
}

void Scene::RemoveNode(Node* node) 
{
	for (auto item = this->nodes.begin(); item != this->nodes.end(); item++)
	{
		if (item->first == node->name) 
		{
			this->nodes.erase(item);
			return;
		}
	}
}

#pragma endregion
