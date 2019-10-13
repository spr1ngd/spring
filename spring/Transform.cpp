#include "transform.h"
#include "gizmos.h"
#include "matrix4x4.h"
#include "console.h"

using namespace spring;

Transform::Transform() 
{

} 

Vector3 Transform::getForword()
{
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 RZ = Matrix4x4::RotateZ(-this->eulerangle.z);
	Matrix4x4 RX = Matrix4x4::RotateX(this->eulerangle.x);
	Matrix4x4 RY = Matrix4x4::RotateY(this->eulerangle.y);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x,this->position.y,this->position.z);
	return IT * RY * RX * RZ * T * this->forword;
}

Vector3 Transform::getBack()
{
	return -this->getForword();
}

Vector3 Transform::getUp()
{
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 RZ = Matrix4x4::RotateZ(-this->eulerangle.z);
	Matrix4x4 RX = Matrix4x4::RotateX(this->eulerangle.x);
	Matrix4x4 RY = Matrix4x4::RotateY(this->eulerangle.y);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x, this->position.y, this->position.z);
	return IT * RY * RX * RZ * T * this->up;
}

Vector3 Transform::getDown()
{
	return -this->getUp();
}

Vector3 Transform::getRight()
{
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 RZ = Matrix4x4::RotateZ(-this->eulerangle.z);
	Matrix4x4 RX = Matrix4x4::RotateX(this->eulerangle.x);
	Matrix4x4 RY = Matrix4x4::RotateY(this->eulerangle.y);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x, this->position.y, this->position.z);
	return IT * RY * RX * RZ * T * this->right;
}

Vector3 Transform::getLeft()
{
	return -this->getRight();
}

void Transform::LookAt(Vector3 target,bool isLocal)
{
	Vector3 src = this->Forword;
	Vector3 dst = Vector3::Normalize(target - this->position);
	float angle = Mathf::Acos(Vector3::Dot(src, dst));
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x, this->position.y, this->position.z);
	Matrix4x4 R = Matrix4x4::RotateY(angle);
	this->Forword = /*IT **/ R */* T **/ this->Forword;
	Console::ErrorFormat("forward %f,%f,%f",this->Forword.x,this->Forword.y,this->Forword.z);
}

void Transform::RotateAround(Vector3 point, Vector3 axis, float angel) 
{
	
}