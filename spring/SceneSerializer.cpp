#include "sceneserializer.h"
#include "jsonserializer.h"
using namespace spring;

SceneSerializer::SceneSerializer()
{

}

void SceneSerializer::Serialize() 
{
	JsonSerializer* jsonSerializer = new JsonSerializer();
	jsonSerializer->Serialize(this->scene);
}

void SceneSerializer::Deserialize() 
{

}