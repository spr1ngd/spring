#include "sceneserializer.h"
#include "jsonserializer.h"
using namespace spring;

SceneSerializer::SceneSerializer(const char* scenePath)
{
	this->scenePath = scenePath;
}

SceneSerializer::SceneSerializer(Scene* scene)
{
	this->scene = scene;
}

void SceneSerializer::Serialize() 
{
	JsonSerializer* jsonSerializer = new JsonSerializer();
	jsonSerializer->Serialize<Scene>(*this->scene);
	jsonSerializer->WriteTo(this->scenePath);
	delete jsonSerializer;
}

void SceneSerializer::Deserialize() 
{
	JsonSerializer* jsonSerializer = new JsonSerializer();
	jsonSerializer->ReadFrom(this->scenePath);
	Scene* scene = jsonSerializer->Deserialize<Scene>();
	scene->Initialize();
}