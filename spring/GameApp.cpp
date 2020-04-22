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

	GameObject* plane = Primitive::CreatePrimitive(Primitive::Type::Quad);
	plane->transform->SetScale(Vector3(10000, 10000, 10000));
	plane->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//plane->transform->SetPosition(Vector3(0.0f, -25.0f, 0.0f));
	plane->transform->SetEulerangle(Vector3(0.0f, 0.0f, 0.0f));
	MeshRenderer* renderer = plane->GetNode<MeshRenderer>();
	renderer->setRenderOrder(5000);

	Texture* tex = TextureLoader::Load("res/texture/standarduv.jpg");
	renderer->material->shader->setTexture("MainTextureData.texture", tex->textureId);

	renderer->material->shader->setColor(MAIN_COLOR, Color::white);
	renderer->material->shader->receiveShadow = true;

	renderer->material = new Material(Shader::Load("editor/gizmos/editor_gizmos_mesh.vs", "editor/gizmos/editor_gizmos_mesh.fs"));
	renderer->material->AlphaBlendFunc(); 
	renderer->material->CullFaceFunc(false);
	renderer->mesh->mode = Mesh::Mode::Triangles;

	// GameObject* triangle = Primitive::CreatePrimitive(Primitive::Type::Triangle);
	// MeshRenderer* Grassrenderer = triangle->GetNode<MeshRenderer>();
	// Grassrenderer->material->AlphaBlendFunc();
	// Grassrenderer->material->DepthTestFunc(true, GL_LESS, false);
	// Texture* grassTex = TextureLoader::Load("res/texture/snow.png");
	// Grassrenderer->material->shader->setTexture("MainTextureData.texture", grassTex->textureId);
	// triangle->transform->SetScale(Vector3(2.0f));
	// triangle->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// 
	// GameObject* cube = Primitive::CreatePrimitive(Primitive::Type::Cube);
	// cube->transform->SetScale(Vector3(2.0f));
	// cube->transform->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
	// 
	// GameObject* cylinder = Primitive::CreatePrimitive(Primitive::Type::Cylinder);
	// cylinder->transform->SetScale(Vector3(2.0f));
	// cylinder->transform->SetPosition(Vector3(-5.0f, 0.0f, 0.0f));
	// 
	// GameObject* cone = Primitive::CreatePrimitive(Primitive::Type::Cone);
	// cone->transform->SetScale(Vector3(2.0f));
	// cone->transform->SetPosition(Vector3(5.0f, 3.0f, 0.0f));
	// 
	// GameObject* sphere = Primitive::CreatePrimitive(Primitive::Type::Sphere);
	// sphere->transform->SetScale(Vector3(2.0f));
	// sphere->transform->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
	// 
	// GameObject* band = Primitive::CreatePrimitive(Primitive::Type::Band);
	// band->transform->SetScale(Vector3(2.0f));
	// band->transform->SetPosition(Vector3(0.0f, 0.0f, 3.0f)); 

	// plant grass on the plane mesh
	GameObject* ground = Primitive::CreatePrimitive(Primitive::Type::Plane);
	ground->name = "GrassGround";
	Material* grassMaterial = new Material(Shader::Load("custom/geometry_grass.vs", "custom/geometry_grass.fs", "custom/geometry_grass.gs"));
	grassMaterial->CullFaceFunc(false);
	// grassMaterial->AlphaBlendFunc();
	grassMaterial->DepthTestFunc(true, GL_LESS, false);
	Texture* grassTex = TextureLoader::Load("res/texture/grass_gradent.jpg");
	Texture* grassAlpha = TextureLoader::Load("res/texture/grass.png");
	grassMaterial->shader->setTexture(MAIN_TEX, grassTex->textureId);
	grassMaterial->shader->setTexture("AlphaTexture", grassAlpha->textureId);
	MeshRenderer* grassRenderer = ground->GetNode<MeshRenderer>();
	grassRenderer->setRenderOrder(3000);
	grassRenderer->material = grassMaterial;

	// GameObject* mobiusband = Primitive::CreatePrimitive(Primitive::Type::Mobiusband);
	// mobiusband->transform->SetScale(Vector3(10.0f));
	// mobiusband->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// 
	// GameObject* mobiusbandGrass = Primitive::CreatePrimitive(Primitive::Type::Mobiusband);
	// Material* grassMaterial = new Material(Shader::Load("custom/geometry_grass.vs", "custom/geometry_grass.fs", "custom/geometry_grass.gs"));
	// Texture* grassTex = TextureLoader::Load("res/texture/snow.png");
	// grassMaterial->AlphaBlendFunc();
	// grassMaterial->DepthTestFunc(true, GL_LESS, false);
	// grassMaterial->shader->setTexture(MAIN_TEX, grassTex->textureId);
	// MeshRenderer* grassRenderer = mobiusbandGrass->GetNode<MeshRenderer>();
	// grassRenderer->setRenderOrder(3000);
	// grassRenderer->material = grassMaterial;
	// mobiusbandGrass->transform->SetScale(Vector3(10.0f));
	// mobiusbandGrass->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// 
	// GameObject* axisGizmos = Primitive::CreateGizmo(Primitive::GizmoType::Move);
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