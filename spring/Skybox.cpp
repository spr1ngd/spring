#include "skybox.h"
#include "camera.h"
#include "renderorder.h"
#include "modelloader.h"

using namespace spring;

Cubemap* spring::Skybox::irradianceCubemap;
Cubemap* spring::Skybox::prefilter;
Texture* spring::Skybox::prebrdf;

Skybox::Skybox()
{
	Mesh& mesh = ModelLoader::Load("obj/cube.obj");
	this->mesh = &mesh;
	this->setRenderOrder(RenderOrder::Skybox);
	this->layer = Layer::Skybox;
}

Skybox::Skybox(Material* material,Cubemap* cubemap) 
{
	Mesh& mesh = ModelLoader::Load("obj/cube.obj");
	this->mesh = &mesh;
	this->setRenderOrder(RenderOrder::Skybox);
	this->material = material;
	this->material->DepthTestFunc(false);
	this->material->CullFaceFunc(false,GL_FRONT);
	this->SetCubemap(cubemap);
	this->layer = Layer::Skybox;
}

void Skybox::SetCubemap(Cubemap* cubemap) 
{
	this->cubemap = cubemap;
	this->material->shader->setCubemap(MAIN_CUBEMAP, this->cubemap);
}

void Skybox::Render() 
{ 
	if (Camera::main->clearFlag != Camera::ClearFlag::Skybox)
		return;
	glDisable(GL_LIGHTING);
	MeshRenderer::Render();
}