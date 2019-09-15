#include "model.h"
#include "graphic.h"

using namespace spring;

Model::Model() 
{
	this->transform = new Transform();
}

Model::Model(const char* filePath,Material* mateiral)
{
	this->transform = new Transform();
	this->loader = new ModelLoader();
	this->loader->Load(filePath);
	this->meshes = this->loader->meshes;
	this->textures = this->loader->loadedTextures;
	this->material = mateiral;
}

void Model::Init() 
{
	for (unsigned int i = 0; i < this->meshes.size(); i++) 
	{
		Mesh* mesh = &meshes[i];
		mesh->Init([&](void)
			{
				GLuint verexLocation = this->material->shader->getLocation(VERTEX);
				glEnableVertexAttribArray(verexLocation);
				glVertexAttribPointer(verexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

				GLuint normalLocation = this->material->shader->getLocation(NORMAL);
				glEnableVertexAttribArray(normalLocation);
				glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

				GLuint texcoordLocation = this->material->shader->getLocation(TEXCOORD);
				glEnableVertexAttribArray(texcoordLocation);
				glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 5));
			});
	}
}

void Model::Render() 
{
	if (this->material->depthTest == true)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
	if (this->material->alphaTest == true)
		glEnable(GL_ALPHA_TEST);
	else
		glDisable(GL_ALPHA_TEST);

	this->material->shader->use();
	for (unsigned int i = 0; i < this->meshes.size(); i++) 
	{
		Mesh* mesh = &meshes[i];
		mesh->Draw([&](void)
			{
				glm::mat4 model = 
					glm::translate(glm::mat4(1.0),glm::vec3(this->transform->position.x,this->transform->position.y,this->transform->position.z))*
					glm::scale(glm::mat4(1.0f),glm::vec3(this->transform->scale.x,this->transform->scale.y,this->transform->scale.z))*
					glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->eulerangle.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->eulerangle.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->eulerangle.z), glm::vec3(0.0f, 0.0f, 1.0f));
				glm::mat4 nm = glm::inverseTranspose(model);

				GLuint mLocation = this->material->shader->getLocation(MATRIX_M);
				glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(model));

				GLuint nmLocation = this->material->shader->getLocation(MATRIX_NM);
				glUniformMatrix4fv(nmLocation,1,GL_FALSE,glm::value_ptr(nm));

				GLuint vLocation = this->material->shader->getLocation(MATRIX_V);
				glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(Graphic::VIEW));

				GLuint pLocation = this->material->shader->getLocation(MATRIX_P);
				glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(Graphic::PROJECTION));
			});
	}
	this->material->shader->disuse();
}