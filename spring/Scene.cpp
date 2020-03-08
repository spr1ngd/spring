#include "scene.h"
#include "console.h"
#include "sceneserializer.h"
#include <time.h>

using namespace spring;

std::map<const char*, Scene*> Scene::scenes;
Scene* Scene::current;

Scene::Scene() 
{
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	char buffer[48];
	sprintf_s(buffer, "scene_%d%d%d%d%d%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	int length = (int)strlen(buffer);
	this->name = (char*)malloc(length * sizeof(char));
	memset(this->name, 0, length);
	strcpy_s(this->name, length + 1, buffer);
	AddScene(this);
}

Scene::Scene(const char* name) 
{
	int length = (int)strlen(name);
	this->name = (char*)malloc(length * sizeof(char));
	memset(this->name, 0, length);
	strcpy_s(this->name, length + 1, name);
	AddScene(this);
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

void Scene::SaveScene() 
{
	char scenePath[128];
	sprintf_s(scenePath,"res/scene/%s.json",Scene::current->name);
	Scene::SaveScene(scenePath, *Scene::current);
}

void Scene::SaveScene(const char* scenePath, Scene& scene)
{
	SceneSerializer sceneSerializer(scene);
	sceneSerializer.scenePath = scenePath;
	sceneSerializer.Serialize();
	Console::LogFormat("[Scene] : save scene [%s] successfully.",scene.name);
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
	this->nodes.push_back(node);
}

void Scene::RemoveNode(Node* node) 
{
	for (auto item = this->nodes.begin(); item != this->nodes.end(); item++)
	{
		Node* nodePtr = *item;
		if (nodePtr == node)
		{
			this->nodes.erase(item);
			return;
		}
	}
}

#pragma endregion
