#include "springengine_scene.h"

void springengine_scene::Awake() 
{

}

void springengine_scene::Update() 
{
	if (Input::GetKeyDown(KeyCode::L)) 
	{
		PRINT_LOG("Load scene data");

		const char* sceneName = "spring";
		Scene::Load(sceneName);
	}
}