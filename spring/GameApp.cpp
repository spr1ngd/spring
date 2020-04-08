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

}

void GameApp::Update() 
{
	if (Input::GetKeyDown(KeyCode::P))
	{
		GameObject* plane = Primitive::CreatePrimitive(Primitive::Type::Cube);
		plane->transform->SetScale(Vector3(500.0f, 0.10f, 500.0f));
		plane->transform->SetPosition(Vector3(0.0f, -5.0f, 0.0f));
	}
}

void GameApp::Destroy() 
{

}