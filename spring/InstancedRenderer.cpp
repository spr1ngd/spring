#include "instancedrenderer.h"

using namespace spring; 

GLsizei vec4Size = sizeof(glm::vec4);
GLsizei mat4Size = sizeof(glm::mat4);
unsigned int instanceVBO;

InstancedRenderer::InstancedRenderer() 
{
	this->enableGPUInstance = true;
}

InstancedRenderer::InstancedRenderer(Material* instancedMaterial) 
{
	this->enableGPUInstance = true;
	this->material = instancedMaterial;
}

void InstancedRenderer::AddInstance(Vector3 position, Vector3 eulerangle, Vector3 scale) 
{
	Transform* trans = new Transform();
	trans->SetPosition(position);
	trans->SetEulerangle(eulerangle);
	trans->SetScale(scale);
	this->instances.push_back(trans);

	glm::mat4 model =
		glm::translate(glm::mat4(1.0), glm::vec3(position.x,position.y,position.z)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(eulerangle.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(eulerangle.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(eulerangle.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(scale.x,scale.y,scale.z));
	glm::mat4 nm = glm::inverseTranspose(model);
	this->matrixes.push_back(model);
	this->normalmatrixes.push_back(nm);
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
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, mat4Size * this->instances.size(), &this->matrixes[0], GL_STATIC_DRAW);

	glBindVertexArray(mesh->VAO);
	GLuint matrixLocation = glGetAttribLocation(this->material->shader->program, "matrix");
	glEnableVertexAttribArray(matrixLocation + 0);
	glVertexAttribPointer(matrixLocation + 0, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)0);
	glVertexAttribDivisor(matrixLocation + 0, 1);

	glEnableVertexAttribArray(matrixLocation + 1);
	glVertexAttribPointer(matrixLocation + 1, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(1 * vec4Size));
	glVertexAttribDivisor(matrixLocation + 1, 1);

	glEnableVertexAttribArray(matrixLocation + 2);
	glVertexAttribPointer(matrixLocation + 2, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(2 * vec4Size));
	glVertexAttribDivisor(matrixLocation + 2, 1);

	glEnableVertexAttribArray(matrixLocation + 3);
	glVertexAttribPointer(matrixLocation + 3, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(3 * vec4Size));
	glVertexAttribDivisor(matrixLocation + 3, 1);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// unsigned int nmVBO;
	// glGenBuffers(1, &nmVBO);
	// glBindBuffer(GL_ARRAY_BUFFER, nmVBO);
	// glBufferData(GL_ARRAY_BUFFER, mat4Size * this->instances.size(), &this->normalmatrixes[0], GL_STATIC_DRAW);
	// 
	// glBindVertexArray(mesh->VAO);
	// GLuint nmLocation = glGetAttribLocation(this->material->shader->program, "normalMatrix");
	// glEnableVertexAttribArray(nmLocation + 0);
	// glVertexAttribPointer(nmLocation + 0, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)0);
	// glVertexAttribDivisor(nmLocation + 0, 1);
	// 
	// glEnableVertexAttribArray(nmLocation + 1);
	// glVertexAttribPointer(nmLocation + 1, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(1 * vec4Size));
	// glVertexAttribDivisor(nmLocation + 1, 1);
	// 
	// glEnableVertexAttribArray(nmLocation + 2);
	// glVertexAttribPointer(nmLocation + 2, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(2 * vec4Size));
	// glVertexAttribDivisor(nmLocation + 2, 1);
	// 
	// glEnableVertexAttribArray(nmLocation + 3);
	// glVertexAttribPointer(nmLocation + 3, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(3 * vec4Size));
	// glVertexAttribDivisor(nmLocation + 3, 1);
	// glBindVertexArray(0);
	// 
	// glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void InstancedRenderer::Render(Camera* camera) 
{
	if (this->material == nullptr)
	{
		Console::Warning("can not render without material,please assign a material.");
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

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); 
	glBufferData(GL_ARRAY_BUFFER, mat4Size * this->instances.size(), &this->matrixes[0], GL_STATIC_DRAW);
	glBindVertexArray(mesh->VAO);

	GLuint matrixLocation = glGetAttribLocation(this->material->shader->program, "matrix");
	glEnableVertexAttribArray(matrixLocation + 0);
	glVertexAttribPointer(matrixLocation + 0, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)0);
	glVertexAttribDivisor(matrixLocation + 0, 1);

	glEnableVertexAttribArray(matrixLocation + 1);
	glVertexAttribPointer(matrixLocation + 1, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(1 * vec4Size));
	glVertexAttribDivisor(matrixLocation + 1, 1);

	glEnableVertexAttribArray(matrixLocation + 2);
	glVertexAttribPointer(matrixLocation + 2, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(2 * vec4Size));
	glVertexAttribDivisor(matrixLocation + 2, 1);

	glEnableVertexAttribArray(matrixLocation + 3);
	glVertexAttribPointer(matrixLocation + 3, 4, GL_FLOAT, GL_FALSE, mat4Size, (void*)(3 * vec4Size));
	glVertexAttribDivisor(matrixLocation + 3, 1);
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection;
	if (this->layer == Layer::UI) projection = camera->Get2DProjection();
	else projection = camera->GetProjectionMatrix();
	// this->material->shader->setMat4(MATRIX_M, model);
	// this->material->shader->setMat4(MATRIX_NM, nm);
	this->material->shader->setMat4(MATRIX_V, view);
	this->material->shader->setMat4(MATRIX_P, projection);

	// draw mesh
	this->material->shader->use();
	mesh->DrawInstanced((unsigned int)this->instances.size());
	this->material->shader->disuse();
}