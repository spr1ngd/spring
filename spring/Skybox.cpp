#include "skybox.h"
#include "console.h"
#include "camera.h"
#include "graphic.h"
#include "renderorder.h"
#include "modelloader.h"

using namespace spring;

Skybox::Skybox(const char* skyboxName, Material material)
{
	auto loader = new ModelLoader();
	loader->Load("res/model/obj/Cube.obj");
	this->meshes = loader->meshes;
	this->textures = loader->loadedTextures;

	this->transform = new Transform();
	this->name = skyboxName;
	this->material = material;
	this->material.depthTest = false;
	this->setRenderOrder(RenderOrder::Skybox);

	TextureLoader cubemapLoader;
	this->cubemap = cubemapLoader.LoadCubemap("res/texture/skybox/night");
};

void Skybox::Init() 
{ 
	for (unsigned int i = 0; i < this->meshes.size(); i++)
	{
		Mesh* mesh = &meshes[i];
		mesh->Init([&](void)
			{
				GLuint locationId = this->material.shader->getLocation(VERTEX);
				glEnableVertexAttribArray(locationId);
				glVertexAttribPointer(locationId, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			});
	}
}

void Skybox::Render() 
{ 
	if (&this->material == nullptr)
	{
		// todo : how to throw exception in c plus plus ,and how to declare custom exception type.
		Console::Warning("can not render skybox without skybox material,please assign a sky box material.");
		return;
	} 
	if (Camera::main->clearFlag != Camera::ClearFlag::Skybox)
		return;
	// this->transform->position = Camera::main->transform->position; 
	// todo : enable lighting or enable depth test and alpha test should be decided by material(shader).
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_BACK, GL_FILL);

	this->material.shader->use();
	for (unsigned int i = 0; i < this->meshes.size(); i++)
	{
		Mesh* mesh = &meshes[i];
		mesh->Draw([&](void)
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0),
					glm::vec3(this->transform->position.x,
						this->transform->position.y,
						this->transform->position.z));

				GLuint mLocation = this->material.shader->getLocation(MATRIX_M);
				glUniformMatrix4fv(mLocation, 1, GL_FALSE, glm::value_ptr(model));

				GLuint vLocation = this->material.shader->getLocation(MATRIX_V);
				glUniformMatrix4fv(vLocation, 1, GL_FALSE, glm::value_ptr(Graphic::VIEW));

				GLuint pLocation = this->material.shader->getLocation(MATRIX_P);
				glUniformMatrix4fv(pLocation, 1, GL_FALSE, glm::value_ptr(Graphic::PROJECTION));
				 
				glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
			});
	}
	this->material.shader->disuse();
}