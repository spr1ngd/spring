#include "transform.h"
#include "gizmos.h"
#include "console.h"

using namespace spring;

Transform::Transform() 
{

}  

void Transform::SetEulerangle(Vector3 eulerangle)
{ 
	Matrix4x4 RZ = Matrix4x4::RotateZ(eulerangle.z); // Matrix4x4::Rotate(eulerangle.z, Vector3::forward); 
	Matrix4x4 RX = Matrix4x4::RotateX(eulerangle.x); // Matrix4x4::Rotate(eulerangle.x, Vector3::right);   
	Matrix4x4 RY = Matrix4x4::RotateY(eulerangle.y); // Matrix4x4::Rotate(eulerangle.y, Vector3::up);      
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

void Transform::Rotate(Vector3 axis, float angle)
{
	// rotate to inertial coordinate
	// distinguish between local coordinate and global coordinate
	// 绕局部坐标系中任意向量进行旋转
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x,this->position.y,this->position.z);
	Matrix4x4 R = Matrix4x4::Rotate(angle, axis);
	// this->rotationMatrix = IT * R * T;
	// this->right = this->rotationMatrix * this->right;
	// this->up = this->rotationMatrix * this->up;
	// this->forword = this->rotationMatrix * this->forword;
	this->position = IT * R * T * this->position;
	// sync to eulerangle
}

void Transform::RotateAround(Vector3 point,Vector3 axis, float angle)
{
	Vector3 offset = this->position - point;
	Matrix4x4 T = Matrix4x4::Translate(-offset.x, -offset.y, -offset.z);
	Matrix4x4 IT = Matrix4x4::Translate(offset.x, offset.y, offset.z);
	axis = Vector3::Normalize(axis);
	Matrix4x4 R = Matrix4x4::Rotate(angle, axis);
	Matrix4x4 mix = IT * R * T;
	this->position = mix * this->position;
}