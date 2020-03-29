#include "gameapp.h"
#include "sample.h"

void GameApp::Awake() 
{
	Sample* sample = new Sample();
	sample->name = "SPRING";
	sample->enabled = true;
}

void GameApp::Update() 
{
	if (Input::GetKeyDown(KeyCode::C)) 
	{
		GameObject plane = Primitive::CreatePrimitive(Primitive::Type::Plane);
		MeshRenderer* renderer = plane.GetNode<MeshRenderer>();
		if (nullptr != renderer) 
		{
			PRINT_LOG("get the renderer node on gameobject.");
			renderer->transform->SetScale(Vector3(100.0f));
		}
	}
}

void GameApp::Destroy() 
{

}