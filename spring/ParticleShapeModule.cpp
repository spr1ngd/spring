#include "particleshapemodule.h"

using namespace spring;

ParticleShapeModule::ParticleShapeModule() 
{
	this->shapeType = ShapeType::Cube;
}

ParticleShapeModule::ParticleShapeModule(Transform* transform) 
{
	this->transform = transform;
	this->shapeType = ShapeType::Cube;
}

void ParticleShapeModule::getSrcParticle(Vector3& position, Vector3& direction) 
{
	position  = this->getSrcPosition();
	direction = this->getDirection();
}

#pragma region calculate source position of particle

Vector3 ParticleShapeModule::getSrcPosition() 
{
	switch (this->shapeType)
	{
	case ShapeType::Cube:
		return this->getSrcPositionInCubeMode();
	case ShapeType::Sphere:
		return this->getSrcPositionInSphereMode();
	case ShapeType::Hemishpere:
		return this->getSrcPositionInHemisphereMode();
	case ShapeType::Cone:
		return this->getSrcPositionInConeMode();
	case ShapeType::Rectangle:
		return this->getSrcPositionInRectangleMode();
	default:
		Console::ErrorFormat("[spring.particlerenderer] : invalid shape type [%s]", this->shapeType);
		return Vector3::zero;
		break;
	}
}

Vector3 ParticleShapeModule::getSrcPositionInCubeMode() 
{
	float halfSize = this->cubeProperties.size * 0.5f;
	float up = Mathf::Randomf(-halfSize, halfSize);
	float right = Mathf::Randomf(-halfSize, halfSize);
	float forward = Mathf::Randomf(-halfSize, halfSize);
	return this->transform->position + this->getDirection() * up + this->transform->right * right + this->transform->forword * forward;
}
Vector3 ParticleShapeModule::getSrcPositionInSphereMode()
{
	// Vector3 direction = this->getDirectionInSphereMode();
	return this->transform->position;// +direction * this->sphereProperties.radius;
}
Vector3 ParticleShapeModule::getSrcPositionInHemisphereMode()
{
	// Vector3 direction = this->getDirectionInHemisphereMode();
	return this->transform->position;
}
Vector3 ParticleShapeModule::getSrcPositionInConeMode() 
{
	// Vector3 direction = this->getDirectionInConeMode();
	return this->transform->position + Vector3(
		Mathf::Randomf(-this->coneProperties.radius,this->coneProperties.radius),
		0.0f,
		Mathf::Randomf(-this->coneProperties.radius,this->coneProperties.radius));
}
Vector3 ParticleShapeModule::getSrcPositionInRectangleMode() 
{
	float halfWidth = this->rectangleProperties.width * 0.5f;
	float halfLength = this->rectangleProperties.length * 0.5f;
	return this->transform->position + Vector3(Mathf::Randomf(-halfWidth,halfWidth),0.0f,Mathf::Randomf(-halfLength,halfLength));
}

#pragma endregion

#pragma region calculate direction of movement

Vector3 ParticleShapeModule::getDirection() 
{
	switch (this->shapeType)
	{
	case ShapeType::Cube:
		return this->getDirectionInCubeMode();
	case ShapeType::Sphere:
		return this->getDirectionInSphereMode();
	case ShapeType::Hemishpere:
		return this->getDirectionInHemisphereMode();
	case ShapeType::Cone:
		return this->getDirectionInConeMode();
	case ShapeType::Rectangle:
		return this->getDirecitonInRectangleMode();
	default:
		Console::ErrorFormat("[spring.particlerenderer] : invalid shape type [%s]",this->shapeType);
		return Vector3::up;
		break;
	}
}

Vector3 ParticleShapeModule::getDirectionInCubeMode() 
{
	return this->transform->up;
}
Vector3 ParticleShapeModule::getDirectionInSphereMode() 
{
	return Vector3::Normalize(Vector3(Mathf::Randomf(-1.0f,1.0f), Mathf::Randomf(-1.0f, 1.0f), Mathf::Randomf(-1.0f, 1.0f)));
}
Vector3 ParticleShapeModule::getDirectionInHemisphereMode() 
{
	Vector3 result = Vector3::Normalize(Vector3(Mathf::Randomf(-1.0f, 1.0f), Mathf::Randomf(0.0f, 1.0f), Mathf::Randomf(-1.0f, 1.0f)));
	result = 
		Matrix4x4::RotateY(this->transform->up.y) *
		Matrix4x4::RotateX(this->transform->up.x) *
		Matrix4x4::RotateZ(this->transform->up.z) * result;
	return result;
}
Vector3 ParticleShapeModule::getDirectionInConeMode() 
{
	float sinHalfAngle = Mathf::Sin(this->coneProperties.angle * 0.5f);
	Vector3 result = Vector3::Normalize(Vector3(Mathf::Randomf(-sinHalfAngle,sinHalfAngle),1.0f,Mathf::Randomf(-sinHalfAngle,sinHalfAngle)));
	result = 
		Matrix4x4::RotateY(this->transform->up.y) *
		Matrix4x4::RotateX(this->transform->up.x) *
		Matrix4x4::RotateZ(this->transform->up.z) * result;
	return result;
}
Vector3 ParticleShapeModule::getDirecitonInRectangleMode() 
{
	return this->transform->up;
}

#pragma endregion