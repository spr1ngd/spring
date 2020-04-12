#include "meshrenderer.h"
#include "graphic.h"
#include "matrix4x4.h"

using namespace spring;

MeshRenderer::MeshRenderer()
{
	this->type = "class spring::MeshRenderer";
}

MeshRenderer::MeshRenderer(Material* mateiral)
{
	PRINT_ERROR("DOES NOT ALLOW CONSTRUCT MESH RENDERER DIRECTLY.");
	this->type = "class spring::MeshRenderer";
	this->material = mateiral;
}

MeshRenderer::~MeshRenderer() 
{
	if (nullptr != this->material)
		delete this->material;
}

void MeshRenderer::Initialize() 
{
	if (this->initialized)
		return;

	if (this->material == nullptr)
	{
		PRINT_WARNING("can not render skybox without skybox material,please assign a sky box material.");
		return;
	} 

	auto initMesh = [&](Mesh* mesh) 
	{
		mesh->Init([&](void)
			{
				GLuint verexLocation = this->material->shader->getAttribLocation(VERTEX);
				glEnableVertexAttribArray(verexLocation);
				glVertexAttribPointer(verexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

				GLuint normalLocation = this->material->shader->getAttribLocation(NORMAL);
				glEnableVertexAttribArray(normalLocation);
				glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));

				GLuint texcoordLocation = this->material->shader->getAttribLocation(TEXCOORD);
				glEnableVertexAttribArray(texcoordLocation);
				glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));

				GLuint colorLocation = this->material->shader->getAttribLocation(COLOR);
				glEnableVertexAttribArray(colorLocation);
				glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
			});
	};

	initMesh(this->mesh);
	// sub mesh
	vector<Mesh*> subMeshes = this->mesh->GetAllSubMeshes();
	for (std::vector<Mesh*>::iterator subMesh = subMeshes.begin(); subMesh != subMeshes.end(); subMesh++) 
		initMesh(*subMesh);

	this->initialized = true;
} 

void MeshRenderer::Destroy() 
{
	delete this;
}

void MeshRenderer::Render() 
{
	this->Render(Camera::current);
}

void MeshRenderer::Render(Camera* camera) 
{
	if (!camera->cullingMask->contains(this->gameobject->layer))
		return;
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection;
	if (this->gameobject->layer == Layer::UI) projection = camera->Get2DProjection();
	else projection = camera->GetProjectionMatrix();
	this->Render(view, projection);
}

void MeshRenderer::Render(glm::mat4 view, glm::mat4 projection)
{
	if (this->material == nullptr)
	{
		PRINT_WARNING("material is null.");
		return;
	}
	if (this->initialized == false)
		this->Initialize();

	if (!this->enabled || ( nullptr != this->gameobject && !this->gameobject->visible) )
		return;

	// this->material->AlphaTestFunc(GL_GREATER, 0.0f);
	this->material->EnableAlphaTest();
	this->material->EnableAlphaBlend();
	this->material->EnableDepthWrite();
	this->material->EnableDepthTest();
	this->material->EnableStencilTest();
	this->material->EnableCullFace();

	auto drawMesh = [&](Mesh* mesh) 
	{
		// if (mesh->textures.size() > 0)
		// {
		// 	vector<Texture*> textures = mesh->textures;
		// 	this->material->shader->setTexture(MAIN_TEX, textures[0]->textureId);
		// }

		// TODO: if model's transform data does not change , model matrix is necessary to recalculate
		glm::mat4 model =
			glm::translate(glm::mat4(1.0), glm::vec3(this->transform->position.x, this->transform->position.y, this->transform->position.z)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().z), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->transform->GetEulerangle().y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(this->transform->scale.x, this->transform->scale.y, this->transform->scale.z));
		glm::mat4 nm = glm::inverseTranspose(model);
		this->material->shader->setMat4(MATRIX_M, model);
		this->material->shader->setMat4(MATRIX_NM, nm);
		this->material->shader->setMat4(MATRIX_V, view);
		this->material->shader->setMat4(MATRIX_P, projection);
		glm::mat4 mvp = projection * view * model;
		this->material->shader->setMat4(MATRIX_MVP, mvp);

		// draw mesh
		this->material->shader->use();
		mesh->Draw();
		this->material->shader->disuse();
	};
	drawMesh(this->mesh);
	// sub mesh
	vector<Mesh*> subMeshes = this->mesh->GetAllSubMeshes();
	for (std::vector<Mesh*>::iterator subMesh = subMeshes.begin(); subMesh != subMeshes.end(); subMesh++)
		drawMesh(*subMesh);
}

MeshRenderer* MeshRenderer::GetMeshRenderer(unsigned int renderableId) 
{
	return static_cast<MeshRenderer*>(Renderable::GetRender(renderableId));
}