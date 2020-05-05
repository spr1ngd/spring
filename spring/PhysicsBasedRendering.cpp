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
	Mesh& mesh = ModelLoader::Load("obj/quad.obj");

	Material* groundMaterial = new Material(Shader::Load("diffuse/diffuse(texture).vs", "diffuse/diffuse(texture).fs"));
	ground = new MeshRenderer(groundMaterial);
	ground->mesh = &mesh;
	ground->Initialize();

	ground->transform->SetLocalScale(Vector3(50.0f));
	ground->transform->SetPosition(Vector3(0.0f, -2.0f, 0.0f));
	ground->transform->SetEulerangle(Vector3(-90.0f, 0.0f, 0.0f));
	ground->material->shader->setColor(MAIN_COLOR, Color::white);
}

void PhysicsBasedRendering::LoadEquirectangularMap(const char* path) 
{
	// todo: 加载等距柱状投影图
}

void PhysicsBasedRendering::CubemapConvolution(Cubemap* cubemap)
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	unsigned int cubemapSize = 64;
	irradiance = TextureLoader::CreateCubemap(cubemapSize, cubemapSize);
	Material* material = new Material(Shader::Load("pbs/cubemap_convolution.vs", "pbs/cubemap_convolution.fs"));
	material->DepthTestFunc(false);
	material->CullFaceFunc(false, GL_FRONT);
	material->shader->setCubemap("environmentCubemap",cubemap);

	Mesh& mesh = ModelLoader::Load("obj/cube.obj");
	GameObject* convolution = new GameObject("Convolution");
	MeshRenderer* meshRenderer = convolution->AddNode<MeshRenderer>();
	meshRenderer->material = material;
	meshRenderer->mesh = &mesh;
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

	FrameBuffer* capture = new FrameBuffer(cubemapSize, cubemapSize);
	capture->colorFormat = ColorFormat::RGB24;
	capture->Initialize();
	glViewport(0, 0, cubemapSize, cubemapSize);
	capture->Bind();
	for (unsigned int i = 0; i < 6; i++) 
	{
		capture->CubemapCapture(irradiance->cubemap, i);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glm::mat4 view = views[i];
		meshRenderer->Render(view, projection);
	}
	capture->Unbind();
	// delete material;
	// delete meshRenderer;
	// delete convolution;
	GameObject::Destroy(convolution);
}

void PhysicsBasedRendering::PreFilter(Cubemap* cubemap) 
{
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	unsigned int cubemapSize = 256;
	unsigned int mipmapLevel = 5;

	prefilter = TextureLoader::CreateCubemapMipmap(cubemapSize, cubemapSize);
	Material* prefilterMaterial = new Material(Shader::Load("pbs/prefilter.vs", "pbs/prefilter.fs"));
	prefilterMaterial->DepthTestFunc(false);
	prefilterMaterial->CullFaceFunc(false, GL_FRONT);
	prefilterMaterial->shader->setCubemap("environmentCubemap", cubemap);

	Mesh& mesh = ModelLoader::Load("obj/cube.obj");
	GameObject* filter = new GameObject("Filter");
	MeshRenderer* meshrenderer = filter->AddNode<MeshRenderer>();
	meshrenderer->material = prefilterMaterial;
	meshrenderer->mesh = &mesh;
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

	FrameBuffer* fbo = new FrameBuffer(cubemapSize,cubemapSize);
	fbo->colorFormat = ColorFormat::RGB24;
	fbo->depthbuffer = FrameBuffer::OnlyDepth;
	fbo->Initialize();

	fbo->Bind();
	for (unsigned int level = 0; level < mipmapLevel; level++) 
	{
		float roughness = static_cast<float>(level) / static_cast<float>((mipmapLevel - 1));
		meshrenderer->material->shader->setFloat("roughness", roughness);

		unsigned int mipmapWidth  = static_cast<int>(cubemapSize * Mathf::Pow(0.5f, (float)level));
		unsigned int minmapHeight = static_cast<int>(cubemapSize * Mathf::Pow(0.5f,(float)level));
		fbo->BindRenderbuffer();
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mipmapWidth, minmapHeight);
		glViewport(0, 0, mipmapWidth, minmapHeight);
		for (unsigned int i = 0; i < 6; i++) 
		{
			fbo->CubemapCapture(prefilter->cubemap, i,level);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glClearColor(0.0f,0.0f,0.0f,1.0f);
			meshrenderer->Render(views[i], projection);
		}
	}
	fbo->Unbind();

	// delete prefilterMaterial;
	// delete meshrenderer;
	GameObject::Destroy(filter);
}

void PhysicsBasedRendering::PreBRDF(Cubemap* cubemap)
{
	unsigned int textureSize = 512;
	prebrdf = TextureLoader::CreateTexture(textureSize,textureSize,0); // TODO : replace GL_RGB TO GL_RG16F
	Material* preBRDFMaterial = new Material(Shader::Load("pbs/prebrdf.vs", "pbs/prebrdf.fs"));
	GameObject* brdf = new GameObject("BRDF");
	FullScreenRenderer* fsRenderer = brdf->AddNode<FullScreenRenderer>();
	fsRenderer->material = preBRDFMaterial;

	glViewport(0, 0, textureSize, textureSize);
	FrameBuffer* fbo = new FrameBuffer(textureSize, textureSize);
	fbo->colorFormat = ColorFormat::RG16;
	fbo->Initialize();
	fbo->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f,0.0f,0.0f,1.0f);
	fsRenderer->Render(glm::mat4(0.0),glm::mat4(0.0));
	fbo->Unbind();

	prebrdf->textureId = fbo->GetBuffer();
	// delete preBRDFMaterial;
	// delete fsRenderer;
	GameObject::Destroy(brdf);
}