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

	for (unsigned int i = 0; i < this->meshes.size(); i++)
	{
		Mesh* mesh = &this->meshes[i];

		// todo : refactor these code
		if (mesh->textures.size() > 0)
		{
			vector<Texture> textures = mesh->textures;
			this->material->shader->setTexture(MAIN_TEX, textures[0].textureId);
		}

		glm::mat4 model =
			glm::translate(glm::mat4(1.0), glm::vec3(this->transform->position.x, this->transform->position.y, this->transform->position.z)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().z), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(this->transform->scale.x, this->transform->scale.y, this->transform->scale.z));
		glm::mat4 nm = glm::inverseTranspose(model);
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection;
		if (this->layer == Layer::UI) projection = camera->Get2DProjection();
		else projection = camera->GetProjectionMatrix();
		this->material->shader->setMat4(MATRIX_M, model);
		this->material->shader->setMat4(MATRIX_NM, nm);
		this->material->shader->setMat4(MATRIX_V, view);
		this->material->shader->setMat4(MATRIX_P, projection);

		// draw mesh
		this->material->shader->use();
		mesh->Draw();
		this->material->shader->disuse();
	}
}