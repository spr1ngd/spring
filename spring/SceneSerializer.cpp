#include "sceneserializer.h"
#include "jsonserializer.h"
using namespace spring;

SceneSerializer::SceneSerializer(Scene& scene):scene(scene)
{

}

void SceneSerializer::Serialize() 
{
	JsonSerializer* jsonSerializer = new JsonSerializer();
	jsonSerializer->Serialize<Scene>(this->scene);
	jsonSerializer->WriteTo(this->scenePath);
	delete jsonSerializer;
}

void SceneSerializer::Deserialize() 
{

}