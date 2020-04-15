#include "gameapp.h"
#include "sample.h"

void GameApp::Awake() 
{
	Sample* sample = new Sample();
	sample->name = "SPRING";
	sample->enabled = true;

	GameObject* internalUICamera = new GameObject("Internal UI Camera");
	internalUICamera->flags = HideFlags::HideFlags_HideInHierarchyWindow;
	Camera* uiCamera = internalUICamera->AddNode<Camera>();
	uiCamera->cullingMask->layers = Layer::UI;
	uiCamera->clearFlag = Camera::None;

	GameObject* plane = Primitive::CreatePrimitive(Primitive::Type::Plane);
	plane->transform->SetScale(Vector3(500, 500, 500));
	plane->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//plane->transform->SetPosition(Vector3(0.0f, -25.0f, 0.0f));
	plane->transform->SetEulerangle(Vector3(-90.0f, 0.0f, 0.0f));
	MeshRenderer* renderer = plane->GetNode<MeshRenderer>();

	Texture* tex = TextureLoader::Load("res/texture/standarduv.jpg");
	renderer->material->shader->setTexture("MainTextureData.texture", tex->textureId);

	renderer->material->shader->setColor(MAIN_COLOR, Color::white);
	renderer->material->shader->receiveShadow = true;

	renderer->material = new Material(Shader::Load("editor/gizmos/editor_gizmos_mesh.vs","editor/gizmos/editor_gizmos_mesh.fs"));
	renderer->material->AlphaBlendFunc();
	renderer->mesh->mode = Mesh::Mode::Triangles;
}

void GameApp::Update() 
{
	if (Input::GetKeyDown(KeyCode::P))
	{
		
	}
}

void GameApp::Destroy() 
{

}