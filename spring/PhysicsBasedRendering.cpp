#include "physicsbasedrendering.h"
#include "springengine.h"
#include "gui.h"
#include "console.h"
#include "fullscreenrenderer.h"

using namespace spring;
using namespace spring::ui;

Cubemap* PhysicsBasedRendering::irradiance;
Cubemap* PhysicsBasedRendering::prefilter;
Texture* PhysicsBasedRendering::prebrdf;

MeshRenderer* ground;
float shaderTimer = 0.0f;
bool init = false;

void DrawGroundxxx()
{
	if (nullptr != ground)
		return;
	ModelLoader* modelloader = new ModelLoader();
	modelloader->Load("res/model/obj/quad.obj");

	Material* groundMaterial = new Material(Shader::Load("diffuse/diffuse(texture).vs", "diffuse/diffuse(texture).fs"));
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
	Cubemap* result = TextureLoader::CreateCubemap(cubemapSize, cubemapSize);
	Shader* irradiance = Shader::Load("pbs/cubemap_convolution.vs","pbs/cubemap_convolution.fs");
	// Shader* irradiance = Shader::Load("unlit/color.vs", "unlit/color.fs");
	Material* material = new Material(irradiance);
	material->DepthTestFunc(false);
	material->CullFaceFunc(false, GL_FRONT);
	material->shader->setCubemap("environmentCubemap",cubemap);

	ModelLoader loader;
	loader.Load("res/model/obj/cube.obj");
	MeshRenderer* meshRenderer = new MeshRenderer(material);
	meshRenderer->name = "PBR CubemapConvolution";
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

	FrameBuffer* capture = FrameBuffer::GenColorFramebuffer(cubemapSize, cubemapSize, 0);
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
	delete irradiance;
	delete material;
	delete meshRenderer;
	return result;
}

Cubemap* PhysicsBasedRendering::PreFilter(Cubemap* cubemap) 
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	unsigned int cubemapSize = 256;
	unsigned int mipmapLevel = 5;

	Cubemap* result = TextureLoader::CreateCubemapMipmap(cubemapSize, cubemapSize);

	Shader* prefilterShader = Shader::Load("pbs/prefilter.vs","pbs/prefilter.fs");
	Material* prefilterMaterial = new Material(prefilterShader);
	prefilterMaterial->DepthTestFunc(false);
	prefilterMaterial->CullFaceFunc(false, GL_FRONT);
	prefilterMaterial->shader->setCubemap("environmentCubemap", cubemap);

	ModelLoader loader;
	loader.Load("res/model/obj/cube.obj");

	MeshRenderer* meshrenderer = new MeshRenderer(prefilterMaterial);
	meshrenderer->name = "PBR PreFilter";
	meshrenderer->meshes = loader.meshes;
	meshrenderer->Init();
	meshrenderer->transform->position = Vector3::zero;

	glm::mat4 views[] =
	{
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f)), // TODO:为什么这里和常规up方向是相反的
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,-1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,-1.0f,0.0f))
	};
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 1000.0f);

	FrameBuffer* fbo = FrameBuffer::GenColorFramebuffer(cubemapSize, cubemapSize);

	fbo->Bind();
	for (unsigned int level = 0; level < mipmapLevel; level++) 
	{
		float roughness = static_cast<float>(level) / static_cast<float>((mipmapLevel - 1));
		meshrenderer->material->shader->setFloat("roughness", roughness);
		PRINT_WARNING("roughness = %f",roughness);

		unsigned int mipmapWidth  = static_cast<int>(cubemapSize * Mathf::Pow(0.5f, (float)level));
		unsigned int minmapHeight = static_cast<int>(cubemapSize * Mathf::Pow(0.5f,(float)level));
		fbo->BindRenderbuffer();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mipmapWidth, minmapHeight);
		glViewport(0, 0, mipmapWidth, minmapHeight);
		for (unsigned int i = 0; i < 6; i++) 
		{
			fbo->CubemapCapture(result->cubemap, i,level);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			meshrenderer->Render(views[i], projection);
		}
	}
	fbo->Unbind();

	delete prefilterMaterial;
	delete prefilterShader;
	delete meshrenderer;
	return result;
}

Texture* PhysicsBasedRendering::PreBRDF(Cubemap* cubemap)
{
	unsigned int textureSize = 512;
	Texture* result = TextureLoader::CreateTexture(textureSize,textureSize,0); // TODO : replace GL_RGB TO GL_RG16F

	Shader* preBRDFShader = Shader::Load("pbs/prebrdf.vs","pbs/prebrdf.fs");
	Material* preBRDFMaterial = new Material(preBRDFShader);

	// render a fullscreen quad
	FullScreenRenderer* fsRenderer = new FullScreenRenderer();
	fsRenderer->name = "FPS(PreBRDF)";
	fsRenderer->Init();
	fsRenderer->material = preBRDFMaterial;

	glViewport(0, 0, textureSize, textureSize);
	FrameBuffer* fbo = FrameBuffer::GenColorFramebuffer(textureSize, textureSize, 0);
	fbo->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f,0.0f,0.0f,1.0f);
	fsRenderer->Render(glm::mat4(0.0),glm::mat4(0.0));
	fbo->Unbind();

	result->textureId = fbo->buffer;
	delete preBRDFShader;
	delete preBRDFMaterial;
	delete fsRenderer;
	return result;
}