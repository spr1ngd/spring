#include "skybox.h"
#include "camera.h"
#include "renderorder.h"
#include "modelloader.h"

using namespace spring;

Skybox::Skybox(Material* material,Cubemap* cubemap) 
{
	ModelLoader* loader = new ModelLoader();
	loader->Load("res/model/obj/Cube.obj");
	this->meshes = loader->meshes;
	delete loader;
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