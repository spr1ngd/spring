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

}

void GameApp::Destroy() 
{

}