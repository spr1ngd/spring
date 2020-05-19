#include "gameapp.h"
#include "sample.h"
#include "thirdplayercamera.h"
#include "gizmos.h"
#include "misc.h"

GameObject* thirdPlayer = nullptr;
MeshRenderer* grassRenderer = nullptr;

void PerformanceTest()
{
	GameObject* parent = Primitive::CreatePrimitive(Primitive::Cube);
	for (unsigned int childIndex = 0; childIndex < 100; childIndex++)
	{
		GameObject* child = Primitive::CreatePrimitive(Primitive::Cube);
		child->name = misc::strcat(std::to_string(childIndex).c_str(),"");
		child->SetParent(parent);
		child->transform->SetPosition(Vector3(Mathf::Randomf(-20.0f, 20.0f), Mathf::Randomf(0.0f, 20.0f), Mathf::Randomf(-20.0f, 20.0f)));
	}
}

void GameApp::Awake()
{
	Sample* sample = new Sample();
	sample->name = "SPRING";
	sample->enabled = true;

	GameObject* internalUICamera = new GameObject("Internal UI Camera");
	internalUICamera->SetFlag(HideFlags::HideFlags_HideInHierarchyWindow);
	Camera* uiCamera = internalUICamera->AddNode<Camera>();
	uiCamera->cullingMask->layers = Layer::UI;
	uiCamera->clearFlag = Camera::None;

	GameObject* plane = Primitive::CreatePrimitive(Primitive::Type::Quad);
	plane->name = "Ground";
	plane->SetFlag(HideFlags_NotEditable);
	plane->transform->SetLocalScale(Vector3(100, 100, 100));
	plane->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//plane->transform->SetPosition(Vector3(0.0f, -25.0f, 0.0f));
	plane->transform->SetEulerangle(Vector3(0.0f, 0.0f, 0.0f));
	MeshRenderer* renderer = plane->GetNode<MeshRenderer>();
	Texture* tex = TextureLoader::Load("res/texture/standarduv.jpg",true);
	renderer->material->shader->setTexture("MainTextureData.texture", tex->textureId);
	renderer->setRenderOrder(5000);
	

	// TODO : ultimate display this model 'nature park' in scene , can keep fps more over 64.
	GameObject* naturepark = ModelLoader::LoadGameObjectFromFile("fbx/mobiusband.fbx");
	naturepark->transform->SetLocalScale(Vector3(0.1f, 0.1f, 0.1f));
	// PerformanceTest();
	return;

	//Texture* tex = TextureLoader::Load("res/texture/standarduv.jpg");
	//renderer->material->shader->setTexture("MainTextureData.texture", tex->textureId);

	//renderer->material->shader->setColor(MAIN_COLOR, Color::white);
	//renderer->material->shader->receiveShadow = true;

	//renderer->material = new Material(Shader::Load("editor/gizmos/editor_gizmos_mesh.vs", "editor/gizmos/editor_gizmos_mesh.fs"));
	//renderer->material->AlphaBlendFunc(); 
	//renderer->material->CullFaceFunc(false);
	//renderer->mesh->mode = Mesh::Mode::Triangles;
	//// 
	//// GameObject* cube = Primitive::CreatePrimitive(Primitive::Type::Cube);
	//// cube->transform->SetScale(Vector3(2.0f));
	//// cube->transform->SetPosition(Vector3(0.0f, 0.0f, -2.0f));
	//// 
	//// GameObject* cylinder = Primitive::CreatePrimitive(Primitive::Type::Cylinder);
	//// cylinder->transform->SetScale(Vector3(2.0f));
	//// cylinder->transform->SetPosition(Vector3(-5.0f, 0.0f, 0.0f));
	//// 
	//// GameObject* cone = Primitive::CreatePrimitive(Primitive::Type::Cone);
	//// cone->transform->SetScale(Vector3(2.0f));
	//// cone->transform->SetPosition(Vector3(5.0f, 3.0f, 0.0f));
	//// 
	//// GameObject* sphere = Primitive::CreatePrimitive(Primitive::Type::Sphere);
	//// sphere->transform->SetScale(Vector3(2.0f));
	//// sphere->transform->SetPosition(Vector3(0.0f, 3.0f, 0.0f));


	//Texture* heightMap = TextureLoader::Load("res/texture/noise.png");
	//GameObject* ground = Primitive::CreatePrimitive(Primitive::Type::Plane);
	//ground->name = "Ground";
	//Texture* grassGround = TextureLoader::Load("res/texture/grass.jpg");
	//MeshRenderer* groundMeshRenderer = ground->GetNode<MeshRenderer>();
	//groundMeshRenderer->material->CullFaceFunc(true);
	//groundMeshRenderer->material->shader->setTexture("MainTextureData.texture",grassGround->textureId);
	//groundMeshRenderer->material->shader->setTilling("MainTextureData", Vector2(10.0f,10.0f));
	//groundMeshRenderer->material->shader->setTexture(HEIGHT_TEX,heightMap->textureId);

	//// GameObject* triangle = Primitive::CreatePrimitive(Primitive::Type::Triangle);
	//// MeshRenderer* triangleRenderer = triangle->GetNode<MeshRenderer>();
	//// triangleRenderer->material->CullFaceFunc(true);
	//// triangleRenderer->material->shader->setTexture("MainTextureData.texture", grassGround->textureId);
	//// triangle->transform->SetScale(Vector3(2.0f));
	//// triangle->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	//// plant grass on the plane mesh
	//GameObject* grass = Primitive::CreatePrimitive(Primitive::Type::Plane);
	//grass->name = "GrassGround";
	//Material* grassMaterial = new Material(Shader::Load("custom/geometry_grass.vs", "custom/geometry_grass.fs", "custom/geometry_grass.gs"));
	//grassMaterial->CullFaceFunc(false);
	//grassMaterial->DepthTestFunc(true, GL_LESS, true);
	//Texture* grassTex = TextureLoader::Load("res/texture/grass_gradent.jpg");
	//Texture* grassAlpha = TextureLoader::Load("res/texture/grass_leaf.png");
	//grassMaterial->shader->setTexture(MAIN_TEX, grassTex->textureId);
	//grassMaterial->shader->setTexture("AlphaTexture", grassAlpha->textureId);
	//grassMaterial->shader->setTexture(HEIGHT_TEX, heightMap->textureId);
	//grassRenderer = grass->GetNode<MeshRenderer>();
	//grassRenderer->setRenderOrder(3000);
	//grassRenderer->material = grassMaterial;
	//// grassRenderer->material->shader->setFloat("FactorRadius", 0.2f);
	// 
	//GameObject* band = Primitive::CreateBand(1.0f, 0.01f, 128, 16);
	//band->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	//// GameObject* mobiusband = Primitive::CreatePrimitive(Primitive::Type::Mobiusband);
	////mobiusband->transform->SetLocalScale(Vector3(10.0f));
	////mobiusband->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//// 
	//// GameObject* mobiusbandGrass = Primitive::CreatePrimitive(Primitive::Type::Mobiusband);
	//// mobiusbandGrass->name = "Mobiusband_Grass";
	//// MeshRenderer* grassRenderer = mobiusbandGrass->GetNode<MeshRenderer>();
	//// grassRenderer->setRenderOrder(3000);
	//// grassRenderer->material = grassMaterial;
	//// mobiusbandGrass->transform->SetScale(Vector3(10.0f));
	//// mobiusbandGrass->transform->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	//// initialize the third player
	//thirdPlayer = Primitive::CreatePrimitive(Primitive::Sphere);
	//thirdPlayer->transform->SetLocalScale(Vector3(0.05f,0.05f,0.05f));
	//thirdPlayer->transform->SetPosition(Vector3(0.0f,0.1f,0.0f));

	//Gizmos::DrawAxis(*thirdPlayer->transform);
}

void GameApp::Update() 
{ 
	return;
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