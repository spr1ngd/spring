#include "transform.h"
#include "gizmos.h"
#include "console.h"

using namespace spring;

Transform::Transform() 
{

} 

Vector3 Transform::getForword()
{
	return this->forword;
}

Vector3 Transform::getBack()
{
	return -this->getForword();
}

Vector3 Transform::getUp()
{
	return this->up;
}

Vector3 Transform::getDown()
{
	return -this->getUp();
}

Vector3 Transform::getRight()
{
	return this->right;
}

Vector3 Transform::getLeft()
{
	return -this->getRight();
}

void Transform::SetEulerangle(Vector3 eulerangle)
{
	Matrix4x4 RZ = Matrix4x4::RotateZ(eulerangle.z);
	Matrix4x4 RX = Matrix4x4::RotateX(eulerangle.x);
	Matrix4x4 RY = Matrix4x4::RotateY(eulerangle.y);
	this->rotationMatrix = RY * RX * RZ;
	this->right = this->rotationMatrix * this->right;
	this->up = this->rotationMatrix * this->up;
	this->forword = this->rotationMatrix * this->forword;
	this->eulerangle = eulerangle;

	// todo : update quaternion
}

const Vector3 Transform::GetEulerangle() 
{
	return this->eulerangle;
}

void Transform::LookAt(Vector3 target,bool isLocal)
{

}

void Transform::RotateAround(Vector3 axis, float angle)
{
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x, this->position.y, this->position.z);

	//
}