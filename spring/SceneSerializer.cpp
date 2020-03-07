#include "sceneserializer.h"
#include "jsonserializer.h"
using namespace spring;

SceneSerializer::SceneSerializer()
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