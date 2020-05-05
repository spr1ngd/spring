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
	this->transformChangedInThisFrame = true;
	
	this->position = position;
	if (nullptr == this->gameobject->parent) 
	{
		this->localPosition = position;
	}
	else
	{ 
		this->localPosition = this->position - this->gameobject->parent->transform->position;
	}
	RecalculateTransform();
	for (GameObject* child : this->gameobject->children)
	{
		auto srcLocalPos = child->transform->GetLocalPosition();
		// child->transform->position = this->position + srcLocalPos;
		// child->transform->RecalculateTransform();
		child->transform->SetPosition(this->position + srcLocalPos);
	}
}

const Vector3& Transform::GetPosition() 
{
	return this->position;
}

void Transform::SetLocalPosition(Vector3 localPosition) 
{
	this->transformChangedInThisFrame = true;

	this->localPosition = localPosition;
	if (nullptr == this->gameobject->parent) 
	{
		this->position = localPosition;
	}
	else 
	{ 
		this->position = this->gameobject->parent->transform->position + localPosition;
	}
	RecalculateTransform();
	for (auto child : this->gameobject->children)
		child->transform->RecalculateTransform();
}

Vector3 Transform::GetLocalPosition() 
{
	return this->localPosition;
}

void Transform::SetLocalScale(Vector3 localScale)
{
	this->transformChangedInThisFrame = true;
	this->localScale = localScale;
	if (nullptr == this->gameobject->parent)
	{
		this->scale = localScale;
	}
	else
	{
		Vector3 parentScale = this->gameobject->parent->transform->scale;
		this->scale = Vector3(parentScale.x * this->localScale.x, parentScale.y * this->localScale.x, parentScale.z * this->localScale.z);
	}
	RecalculateTransform();
	for (GameObject* child : this->gameobject->children)
	{
		Vector3 srcLocalScale = child->transform->GetLocalScale();
		child->transform->SetLocalScale(srcLocalScale);
	}
}

const Vector3& Transform::GetLocalScale() 
{
	return this->localScale;
}

void Transform::LookAt(Vector3 target,bool isLocal)
{

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

void Transform::RecalculateTransform() 
{
	this->mMatrix =
		glm::translate(glm::mat4(1.0), glm::vec3(this->position.x, this->position.y, this->position.z)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->eulerangle.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->eulerangle.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(this->eulerangle.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(this->scale.x, this->scale.y, this->scale.z));

	//if (nullptr != this->gameobject->parent)
	//{
	//	glm::mat4 M = this->gameobject->parent->transform->GetModelMatrix();
	//	this->mMatrix = M * this->mMatrix;
	//}
	this->nmMatrix = glm::inverseTranspose(this->mMatrix);
	this->transformChangedInThisFrame = false;
}

glm::mat4& Transform::GetModelMatrix() 
{
	if (this->transformChangedInThisFrame)
		this->RecalculateTransform();
	return this->mMatrix;
}

glm::mat4& Transform::GetNMMatrix() 
{
	if (this->transformChangedInThisFrame)
		this->RecalculateTransform();
	return this->nmMatrix;
}

void Transform::SetParent(Transform& parent) 
{
	this->parent = &parent;
	parent.children.push_back(this);
}

Transform* Transform::GetParent() 
{
	return this->parent;
}

Transform* Transform::QueryChild(unsigned int childIndex)
{
	if (childIndex >= this->children.size())
		return nullptr;
	return this->children[childIndex];
}

Transform* Transform::QueryChild(const char* childPath)
{
	for (Transform* child : this->children)
	{
		if (strcmp(child->gameobject->name, childPath) == 0)
			return child;
	}
	return nullptr;
}

unsigned int Transform::GetChildCount() 
{
	return this->children.size();
}