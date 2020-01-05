#include "physicsbasedrendering.h"
#include "springengine.h"
#include "gui.h"

using namespace spring;
using namespace spring::ui;

MeshRenderer* ground;
bool init = false;

void DrawGroundxxx()
{
	if (nullptr != ground)
		return;
	ModelLoader* modelloader = new ModelLoader();
	modelloader->Load("res/model/obj/quad.obj");

	Material* groundMaterial = new Material("res/shader/diffuse/diffuse(texture).vs", "res/shader/diffuse/diffuse(texture).fs");
	ground = new MeshRenderer(groundMaterial);
	ground->meshes = modelloader->meshes;
	ground->textures = modelloader->loadedTextures;
	ground->Init();

	ground->transform->SetScale(Vector3(50.0f));
	ground->transform->SetPosition(Vector3(0.0f, -2.0f, 0.0f));
	ground->transform->SetEulerangle(Vector3(-90.0f, 0.0f, 0.0f));
	ground->material->shader->setColor(MAIN_COLOR, Color::white);
}

void PhysicsBasedRendering::LoadEquirectangularMap(const char* path) 
{
	// todo: 加载等距柱状投影图
}

Cubemap* PhysicsBasedRendering::CubemapConvolution(Cubemap* cubemap)
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	unsigned int cubemapSize = 64;
	Cubemap* result = TextureLoader::CreateCubemap(cubemapSize, cubemapSize, 0);
	Shader* irradiance = Shader::Load("pbs/cubemap_convolution.vs","pbs/cubemap_convolution.fs");
	// Shader* irradiance = Shader::Load("unlit/color.vs", "unlit/color.fs");
	Material* material = new Material(irradiance);
	material->DepthTestFunc(false);
	material->CullFaceFunc(false, GL_FRONT);
	material->shader->setCubemap("environmentCubemap",cubemap);

	ModelLoader loader;
	loader.Load("res/model/obj/cube.obj");
	MeshRenderer* meshRenderer = new MeshRenderer(material);
	meshRenderer->meshes = loader.meshes;
	meshRenderer->Init();
	meshRenderer->transform->position = Vector3::zero;

	glm::mat4 views[] =
	{
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f)), // TODO:为什么这里和常规up方向是相反的
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,-1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,-1.0f,0.0f))
	};
	glm::mat4 projection = glm::perspective(glm::radians(90.0f),1.0f, 0.1f, 1000.0f);

	FrameBufferObject* capture = FrameBufferObject::GenColorFramebuffer(cubemapSize, cubemapSize, 0);
	glViewport(0, 0, cubemapSize, cubemapSize);
	capture->Bind();
	for (unsigned int i = 0; i < 6; i++) 
	{
		capture->CubemapCapture(result->cubemap, i);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glm::mat4 view = views[i];
		meshRenderer->Render(view, projection);
	}
	capture->Unbind();
	delete meshRenderer;
	return result;
}
