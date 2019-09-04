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
			glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 0.0f, -1.0f));
			glm::mat4 view = glm::lookAt(glm::vec3(0.0f,0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

			GLuint mLocation = this->material->shader->getLocation(MATRIX_M);
			glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(model));

			GLuint vLocation = this->material->shader->getLocation(MATRIX_V);
			glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(view));

			GLuint pLocation = this->material->shader->getLocation(MATRIX_P);
			glUniformMatrix4fv(pLocation,1,GL_FALSE,glm::value_ptr(projection));
		});
	this->material->shader->disuse();
}