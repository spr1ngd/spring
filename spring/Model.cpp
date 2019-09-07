#include "Model.h"

using namespace spring;

Model::Model() 
{
	this->transform = new Transform();
}

Model::Model(const char* filePath)
{
	this->transform = new Transform();
	this->loader = new ModelLoader();
	this->loader->Load(filePath);
	this->meshes = this->loader->meshes;
	this->textures = this->loader->loadedTextures;
} 

void Model::Init() 
{
	for (unsigned int i = 0; i < this->meshes.size(); i++) 
	{
		Mesh* mesh = &meshes[i];
		mesh->Init([&](void)
			{
				GLuint locationId = this->material->shader->getLocation(VERTEX);
				glEnableVertexAttribArray(locationId);
				// todo : fixed one 
				glVertexAttribPointer(locationId, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			});
	}
}

void Model::Render( glm::mat4 view,glm::mat4 projection ) 
{
	this->material->shader->use();
	for (unsigned int i = 0; i < this->meshes.size(); i++) 
	{
		Mesh* mesh = &meshes[i];
		mesh->Draw([&](void)
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0),
					glm::vec3(this->transform->position.x,
						this->transform->position.y,
						this->transform->position.z));

				GLuint mLocation = this->material->shader->getLocation(MATRIX_M);
				glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(model));

				GLuint vLocation = this->material->shader->getLocation(MATRIX_V);
				glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(view));

				GLuint pLocation = this->material->shader->getLocation(MATRIX_P);
				glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(projection));
			});
	}
	this->material->shader->disuse();
}