#include "physicsbasedrendering.h"

using namespace spring;

void PhysicsBasedRendering::LoadEquirectangularMap(const char* path) 
{
	// todo: ���صȾ���״ͶӰͼ
}

Cubemap* PhysicsBasedRendering::CubemapConvolution(Cubemap* cubemap)
{
	Cubemap* result = TextureLoader::CreateCubemap(32, 32, 0);
	// ���ø��������ͶӰ���󣬲�����Ⱦ����洢��FrameBufferObject
	// TODO: 1.���ر������ھ���������������ɫ��
	// TODO: 2.����ͶӰ����
	// TODO: 3.������6������Ⱦ��֡����
	Shader* irradiance = Shader::Load("pbs/cubemap_convolution.vs","pbs/cubemap_convolution.fs");
	Material* material = new Material(irradiance);
	material->shader->setCubemap("environmentCubemap",cubemap);

	ModelLoader loader;
	loader.Load("res/model/obj/cube.obj");
	MeshRenderer* meshRenderer = new MeshRenderer(material);
	meshRenderer->meshes = loader.meshes;
	meshRenderer->Init();
	meshRenderer->transform->position = Vector3::zero;
	// do not forget configure the viewport to the capture dimension

	glm::mat4 views[] =
	{
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),glm::vec3(0.0f,1.0f,0.0f)),
		glm::lookAt(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),glm::vec3(0.0f,1.0f,0.0f))
	};
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), static_cast<float>(Screen::width) / static_cast<float>(Screen::height), 0.1f, 100.0f);

	FrameBufferObject* capture = FrameBufferObject::GenColorFramebuffer(32, 32, 0);

	// glViewport(0, 0, 32, 32);
	capture->Bind();
	for (unsigned int i = 0; i < 6; i++) 
	{
		capture->CubemapCapture(i);
		glm::mat4 view = views[i];
		meshRenderer->Render(view, projection);
	}
	capture->Unbind();
	return result;
}