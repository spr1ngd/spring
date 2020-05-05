#include "gizmos.h"
#include "transform.h"
#include "matrix4x4.h"
#include "console.h"
#include "modelloader.h"

using namespace std;
using namespace spring;
 
bool Gizmos::enable = false;
// vector<AxisHelper*> Gizmos::axisHelpers;
AxisHelper* Gizmos::axisHelper;
vector<Gizmos*> Gizmos::gizmos;
CoordinateSpace Gizmos::space = CoordinateSpace::World;
Colorf Gizmos::color = Colorf::gray; 

void Gizmos::DrawLine(Vector3 origin, Vector3 end) 
{
} 

void Gizmos::DrawCircle(Vector3 pos, Vector3 up, float radius, unsigned int smoothness)
{

} 

void Gizmos::Render() 
{

}

void Gizmos::DrawAxis(Transform& target) 
{
	if (axisHelper == nullptr)
	{
		GameObject* axisGameObject = new GameObject("axis");
		AxisHelper* axis = axisGameObject->AddNode<AxisHelper>();
		axisHelper = axis;
		// axisGameObject->flags = HideFlags_HideInHierarchyWindow;
		// axisHelpers.push_back(axis);
	}
	axisHelper->SetTarget(&target);
}

void Gizmos::SetAxisMode(AxisHelper::EditorGizmosMode mode) 
{
	if (nullptr != axisHelper)
		axisHelper->SetAxisMode(mode);
}