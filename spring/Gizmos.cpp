#include "gizmos.h"
#include "transform.h"

using namespace std;
using namespace spring;

vector<AxisHelper*> Gizmos::axisHelpers;

void Gizmos::DrawAxis(Vector3 pos)
{

}

void Gizmos::DrawAxis(Transform* transform)
{
	AxisHelper* axis = new AxisHelper(transform);
	axisHelpers.push_back(axis);
}

void Gizmos::DrawLine(Vector2 start, Vector2 end) 
{

}

void Gizmos::DrawVector(Vector2 vec2)  
{

}

void Gizmos::Render() 
{
	for (auto pair : axisHelpers) 
		pair->Render();
}