#include "instancedrenderer.h"

using namespace spring; 

InstancedRenderer::InstancedRenderer() 
{

}

InstancedRenderer::InstancedRenderer(Material* instancedMaterial) 
{
	this->material = instancedMaterial;
}

void InstancedRenderer::AddInstance(Vector3 position, Vector3 eulerangle, Vector3 scale) 
{
	Transform* trans = new Transform();
	trans->SetPosition(position);
	trans->SetEulerangle(eulerangle);
	trans->SetScale(scale);
	this->instances.push_back(trans);
}

void InstancedRenderer::Init() 
{
	if (this->material == nullptr)
	{
		Console::Warning("can not render skybox without skybox material,please assign a sky box material.");
		return;
	}

	Mesh* mesh = &this->mesh;

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
			glVertexAttribPointer(colorLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));

		});

	GLsizei vec4Size = sizeof(glm::vec4);
	GLsizei mat4Size = sizeof(glm::mat4);
	unsigned int instanceVBO;
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, mat4Size, &this->matrixes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint matrixLocation = glGetUniformLocation(this->material->shader->program, "matrix");
	glEnableVertexAttribArray(matrixLocation + 0);
	glVertexAttribPointer(matrixLocation + 0, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)0);
}

void InstancedRenderer::Render(Camera* camera) 
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

	Mesh* mesh = &this->mesh;

	if (mesh->textures.size() > 0)
	{
		vector<Texture> textures = mesh->textures;
		this->material->shader->setTexture(MAIN_TEX, textures[0].textureId);
	}

	// todo : update matrixes vector.

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
	mesh->DrawWithGPUInstanced(this->instances.size());
	this->material->shader->disuse();
}