#include "transform.h"
#include "gizmos.h"
#include "console.h"

using namespace spring;

Transform::Transform() 
{

}  

void Transform::SetEulerangle(Vector3 eulerangle)
{
	Matrix4x4 RZ = Matrix4x4::RotateZ(eulerangle.z);
	Matrix4x4 RX = Matrix4x4::RotateX(eulerangle.x);
	Matrix4x4 RY = Matrix4x4::RotateY(eulerangle.y);
	this->rotationMatrix =  RY * RX * RZ;
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
}

void Transform::RotateAround(Vector3 point,Vector3 axis, float angle)
{
	Vector3 offset = this->position - point;
	Matrix4x4 T = Matrix4x4::Translate(-offset.x, -offset.y, -offset.z);
	Matrix4x4 IT = Matrix4x4::Translate(offset.x, offset.y, offset.z);
	// todo : Matrix4x4 rotate has bug in x and z axis.
	Matrix4x4 R = Matrix4x4::Rotate(angle, axis);
	Matrix4x4 mix = IT * R * T;
	this->position = mix * this->position;
}