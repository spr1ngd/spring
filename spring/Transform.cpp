#include "transform.h"
#include "gizmos.h"
#include "console.h"

using namespace spring;

Transform::Transform() 
{

}  

void Transform::SetEulerangle(Vector3 eulerangle)
{ 
	Matrix4x4 T = Matrix4x4::Translate(-this->position.x, -this->position.y, -this->position.z);
	Matrix4x4 IT = Matrix4x4::Translate(this->position.x,this->position.y,this->position.z);
	Matrix4x4 RZ = Matrix4x4::RotateZ(eulerangle.z);
	Matrix4x4 RX = Matrix4x4::RotateX(eulerangle.x);
	Matrix4x4 RY = Matrix4x4::RotateY(eulerangle.y);
	this->rotationMatrix = IT * RY * RX * RZ * T;
	this->right = this->rotationMatrix * Vector3::right;
	this->up = this->rotationMatrix * Vector3::up;
	this->forword = this->rotationMatrix * Vector3::forward;
	this->eulerangle = eulerangle;
	this->rotation = Quaternion::Euler(this->eulerangle);
}

const Vector3& Transform::GetEulerangle() 
{
	return this->eulerangle;
}

void Transform::SetRotation(Quaternion rotation) 
{
	this->rotation = rotation;
	// this->SetEulerangle(this->rotation.EulerAngle());
	// this->eulerangle = this->rotation.EulerAngle();
	// Console::ErrorFormat("%f,%f,%f", this->eulerangle.x, this->eulerangle.y, this->eulerangle.z);
	// todo : update eulerangle and rotation matrix
}

const Quaternion& Transform::GetRotation() 
{
	return this->rotation;
}

void Transform::SetPosition(Vector3 position) 
{
	this->position = position;
}

const Vector3& Transform::GetPosition() 
{
	return this->position;
}

void Transform::SetScale(Vector3 scale) 
{
	this->scale = scale;
}

const Vector3& Transform::GetScale() 
{
	return this->scale;
}

void Transform::LookAt(Vector3 target,bool isLocal)
{
	// todo : 
	// set transform eulerangle.
}

void Transform::Rotate(Vector3 axis, float angle)
{

}

void Transform::RotateAround(Vector3 point,Vector3 axis, float angle)
{
	Vector3 offset = this->position - point; 
	Matrix4x4 T = Matrix4x4::Translate(-offset.x, -offset.y, -offset.z);
	Matrix4x4 IT = Matrix4x4::Translate(offset.x, offset.y, offset.z);
	// axis = Vector3::Normalize(axis);
	Matrix4x4 R = Matrix4x4::Rotate(angle, axis);
	Matrix4x4 mix = IT * R * T;
	this->position = point + mix * offset;
}