#include "meshrenderer.h"
#include "mesh.h"
#include "graphic.h"
#include "matrix4x4.h"
#include "graphicprofiler.h"

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
	this->Render(camera->GetViewMatrix(), 
		this->gameobject->layer == Layer::UI ? camera->Get2DProjection() : camera->GetProjectionMatrix());
}

void MeshRenderer::Render(const glm::mat4& view, const glm::mat4& projection)
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

	glm::mat4 model = this->transform->GetModelMatrix();
	glm::mat4 nm = this->transform->GetNMMatrix();

	GraphicProfiler::BeginSample("enable shader");
	this->material->shader->use();  
	GraphicProfiler::EndSample();

	GraphicProfiler::BeginSample("draw mesh");
	this->RenderMesh(this->material, this->mesh, model, nm, view, projection);
	GraphicProfiler::EndSample();
	// sub mesh
	vector<Mesh*> subMeshes = this->mesh->GetAllSubMeshes();
	for (std::vector<Mesh*>::iterator subMesh = subMeshes.begin(); subMesh != subMeshes.end(); subMesh++)
		this->RenderMesh(this->material, *subMesh, model, nm, view, projection);
	this->material->shader->disuse();
}

void MeshRenderer::RenderMesh(Material* mat, Mesh* mesh, const glm::mat4& model, const glm::mat4& nm, const glm::mat4& view, const glm::mat4 projection)
{
	glm::mat4 mvp = projection * view * model;
	mat->shader->setMat4(MATRIX_M, model);
	mat->shader->setMat4(MATRIX_NM, nm);
	mat->shader->setMat4(MATRIX_V, view);
	mat->shader->setMat4(MATRIX_P, projection);
	mat->shader->setMat4(MATRIX_MVP, mvp);
	mesh->Draw();
}

MeshRenderer* MeshRenderer::GetMeshRenderer(unsigned int renderableId) 
{
	return static_cast<MeshRenderer*>(Renderable::GetRender(renderableId));
}