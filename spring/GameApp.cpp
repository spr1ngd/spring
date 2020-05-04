#include "gameapp.h"
#include "sample.h"
#include "thirdplayercamera.h"
#include "gizmos.h"

GameObject* thirdPlayer = nullptr;
MeshRenderer* grassRenderer = nullptr;

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

	Texture* heightMap = TextureLoader::Load("res/texture/noise.png");
	GameObject* ground = Primitive::CreatePrimitive(Primitive::Type::Plane);
	ground->name = "Ground";
	Texture* grassGround = TextureLoader::Load("res/texture/grass.jpg");
	MeshRenderer* groundMeshRenderer = ground->GetNode<MeshRenderer>();
	groundMeshRenderer->material->CullFaceFunc(true);
	groundMeshRenderer->material->shader->setTexture("MainTextureData.texture",grassGround->textureId);
	groundMeshRenderer->material->shader->setTilling("MainTextureData", Vector2(10.0f,10.0f));
	groundMeshRenderer->material->shader->setTexture("HeightMap",heightMap->textureId);

	// GameObject* triangle = Primitive::CreatePrimitive(Primitive::Type::Triangle);
	// MeshRenderer* triangleRenderer = triangle->GetNode<MeshRenderer>();
	// triangleRenderer->material->CullFaceFunc(true);
	// triangleRenderer->material->shader->setTexture("MainTextureData.texture", grassGround->textureId);
	// triangle->transform->SetScale(Vector3(2.0f));
	// triangle->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	// plant grass on the plane mesh
	GameObject* grass = Primitive::CreatePrimitive(Primitive::Type::Plane);
	grass->name = "GrassGround";
	Material* grassMaterial = new Material(Shader::Load("custom/geometry_grass.vs", "custom/geometry_grass.fs", "custom/geometry_grass.gs"));
	grassMaterial->CullFaceFunc(false);
	grassMaterial->DepthTestFunc(true, GL_LESS, true);
	Texture* grassTex = TextureLoader::Load("res/texture/grass_gradent.jpg");
	Texture* grassAlpha = TextureLoader::Load("res/texture/grass_leaf.png");
	grassMaterial->shader->setTexture(MAIN_TEX, grassTex->textureId);
	grassMaterial->shader->setTexture("AlphaTexture", grassAlpha->textureId);
	grassMaterial->shader->setTexture("HeightMap", heightMap->textureId);
	grassRenderer = grass->GetNode<MeshRenderer>();
	grassRenderer->setRenderOrder(3000);
	grassRenderer->material = grassMaterial;
	// grassRenderer->material->shader->setFloat("FactorRadius", 0.2f);

	// GameObject* mobiusband = Primitive::CreatePrimitive(Primitive::Type::Mobiusband);
	// mobiusband->transform->SetScale(Vector3(10.0f));
	// mobiusband->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	// 
	// GameObject* mobiusbandGrass = Primitive::CreatePrimitive(Primitive::Type::Mobiusband);
	// mobiusbandGrass->name = "Mobiusband_Grass";
	// MeshRenderer* grassRenderer = mobiusbandGrass->GetNode<MeshRenderer>();
	// grassRenderer->setRenderOrder(3000);
	// grassRenderer->material = grassMaterial;
	// mobiusbandGrass->transform->SetScale(Vector3(10.0f));
	// mobiusbandGrass->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	// initialize the third player
	thirdPlayer = Primitive::CreatePrimitive(Primitive::Sphere);
	thirdPlayer->transform->SetScale(Vector3(0.05f,0.05f,0.05f));
	thirdPlayer->transform->SetPosition(Vector3(0.0f,0.1f,0.0f));

	Gizmos::DrawAxis(*thirdPlayer->transform);
}

void GameApp::Update() 
{ 
	// third player camera.
	ThirdPlayerCamera* tpc = Camera::main->gameobject->GetNode<ThirdPlayerCamera>();
	if (nullptr != tpc)
		tpc->target = thirdPlayer;

	grassRenderer->material->shader->setVec3("FactorPos", thirdPlayer->transform->position);

	Vector3 moveDirection = Vector3::zero;
	bool move = false;
	if (Input::GetKey(KeyCode::D)) 
	{
		move = true;
		moveDirection += Vector3::left;
	}
	if (Input::GetKey(KeyCode::A)) 
	{
		move = true;
		moveDirection += Vector3::right;
	}
	if (Input::GetKey(KeyCode::W))
	{
		move = true;
		moveDirection += Vector3::forward;
	}
	if (Input::GetKey(KeyCode::S))
	{
		move = true;
		moveDirection += Vector3::back;
	}
	if (move == true) 
	{
		thirdPlayer->transform->position += Vector3::Normalize(moveDirection) * 0.02f;
	}
}

void GameApp::Destroy() 
{

}