#include "Model.h"

using namespace spring;

Model::Model(const char* filePath)
{

}

Model::Model(Mesh* mesh,Material*material) 
{
	this->mesh = mesh;
	this->material = material;
}

void Model::Init() 
{
	this->mesh->Init([&](void) 
		{
			GLuint locationId = this->material->shader->getLocation(VERTEX);
			glEnableVertexAttribArray(locationId);
			glVertexAttribPointer(locationId,3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
		});
}

void Model::Render() 
{
	this->material->shader->use();
	this->mesh->Draw([&](void)
		{

		});
	this->material->shader->disuse();
}