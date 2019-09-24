#include "transform.h"
#include "gizmos.h"

using namespace spring;

Transform::Transform() 
{

} 

Vector3 Transform::getForword()
{
	return Vector3::forward;
}

Vector3 Transform::getBack()
{
	return Vector3::back;
}

Vector3 Transform::getUp()
{
	return Vector3::up;
}

Vector3 Transform::getDown()
{
	return Vector3::down;
}

Vector3 Transform::getRight()
{
	return Vector3::right;
}

Vector3 Transform::getLeft()
{
	return Vector3::left;
}

void Transform::LookAt(Vector3 target, Vector3 worldUp)
{
	// todo : use matrix to rotate transform
}

void Transform::RotateAround(Vector3 point, Vector3 axis, float angel) 
{
	
}