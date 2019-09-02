#include "Model.h"

using namespace spring;

Model::Model(const char* filePath)
{
	loader = ModelLoader();
	loader.Load(filePath);
}