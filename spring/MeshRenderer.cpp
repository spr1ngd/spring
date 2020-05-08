#include "meshrenderer.h"
#include "mesh.h"
#include "graphic.h"
#include "matrix4x4.h"

using namespace spring;

MeshRenderer::MeshRenderer() : material(nullptr), mesh(nullptr)
{
}

MeshRenderer::MeshRenderer(Material* mateiral) : material(nullptr), mesh(nullptr)
{
	PRINT_ERROR("DOES NOT ALLOW CONSTRUCT MESH RENDERER DIRECTLY.");
	this->material = mateiral;
}

MeshRenderer::~MeshRenderer() 
{
	if (nullptr != this->material)
		delete this->material;
	// Renderable::~Renderable();
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

	if (!this->enabled || ( nullptr != this->gameobject && !this->gameobject->GetActive()) )
		return;

	// this->material->AlphaTestFunc(GL_GREATER, 0.0f);
	this->material->EnableAlphaTest();
	this->material->EnableAlphaBlend();
	this->material->EnableDepthWrite();
	this->material->EnableDepthTest();
	// this->material->EnableStencilTest();
	this->material->EnableCullFace();

	auto drawMesh = [&](Mesh* mesh) 
	{
		glm::mat4 model = this->transform->GetModelMatrix();
		glm::mat4 nm = this->transform->GetNMMatrix();
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