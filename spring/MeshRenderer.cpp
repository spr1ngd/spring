#include "meshrenderer.h"
#include "graphic.h"
#include "matrix4x4.h"

using namespace spring;

MeshRenderer::MeshRenderer() 
{
}

MeshRenderer::MeshRenderer(Material* mateiral)
{
	this->material = mateiral;
}

void MeshRenderer::Init() 
{
	if (this->material == nullptr)
	{
		Console::Warning("can not render skybox without skybox material,please assign a sky box material.");
		return;
	}
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
				glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

				GLuint colorLocation = this->material->shader->getLocation(COLOR);
				glEnableVertexAttribArray(colorLocation);
				glVertexAttribPointer(colorLocation,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float) * 8));
			});

		// todo : refactor these code
		vector<Texture> textures = mesh->textures;
		for (vector<Texture>::iterator item = textures.begin(); item != textures.end(); item++) 
			this->material->shader->setTexture(MAIN_TEX, item->textureId);
	}
} 

void MeshRenderer::Render() 
{
	this->Render(Camera::current);
}

void MeshRenderer::Render(Camera* camera) 
{
	if (this->material == nullptr)
	{
		Console::Warning("can not render skybox without skybox material,please assign a sky box material.");
		return;
	}

	if (!camera->cullingMask->contains(this->layer))
		return;

	this->material->EnableAlphaTest();
	this->material->EnableAlphaBlend();
	this->material->EnableDepthTest();
	this->material->EnableStencilTest();
	this->material->EnableCullFace();

	this->material->shader->use();
	for (unsigned int i = 0; i < this->meshes.size(); i++)
	{
		Mesh* mesh = &meshes[i];
		mesh->Draw([&](void)
			{
				glm::mat4 model =
					glm::translate(glm::mat4(1.0), glm::vec3(this->transform->position.x, this->transform->position.y, this->transform->position.z)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().z), glm::vec3(0.0f, 0.0f, 1.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().x), glm::vec3(1.0f, 0.0f, 0.0f)) *
					glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().y), glm::vec3(0.0f, 1.0f, 0.0f)) *
					glm::scale(glm::mat4(1.0f), glm::vec3(this->transform->scale.x, this->transform->scale.y, this->transform->scale.z));
				glm::mat4 nm = glm::inverseTranspose(model);

				GLuint mLocation = this->material->shader->getLocation(MATRIX_M);
				glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(model));

				GLuint nmLocation = this->material->shader->getLocation(MATRIX_NM);
				glUniformMatrix4fv(nmLocation, 1, GL_FALSE, glm::value_ptr(nm));

				GLuint vLocation = this->material->shader->getLocation(MATRIX_V);
				glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

				GLuint pLocation = this->material->shader->getLocation(MATRIX_P);
				switch (this->layer)
				{
				case Layer::UI:
					glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(camera->Get2DProjection()));
					break;
				default:
					glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));
					break;
				}
			});
	}
	this->material->shader->disuse();
}