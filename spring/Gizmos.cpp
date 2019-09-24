#include "gizmos.h"

using namespace std;
using namespace spring;

vector<AxisHelper*> Gizmos::axisHelpers;

void Gizmos::DrawAxis(Vector3 pos) 
{
	AxisHelper axisHelper;
	axisHelper.Render();
	axisHelper.meshRenderer->transform->position = pos;
}

void Gizmos::DrawLine(Vector2 start, Vector2 end) 
{

}

void Gizmos::DrawVector(Vector2 vec2)  
{

}