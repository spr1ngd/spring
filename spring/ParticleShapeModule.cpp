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
	Vector3 direction = this->getDirectionInSphereMode();
	return this->transform->position;// +direction * this->sphereProperties.radius;
}
Vector3 ParticleShapeModule::getSrcPositionInHemisphereMode()
{
	return Vector3::zero;
}
Vector3 ParticleShapeModule::getSrcPositionInConeMode() 
{
	return Vector3::zero;
}
Vector3 ParticleShapeModule::getSrcPositionInRectangleMode() 
{
	return Vector3::zero;
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
	return transform->up;
}
Vector3 ParticleShapeModule::getDirectionInSphereMode() 
{
	return Vector3::Normalize(Vector3(Mathf::Randomf(-1.0f,1.0f), Mathf::Randomf(-1.0f, 1.0f), Mathf::Randomf(-1.0f, 1.0f)));
}
Vector3 ParticleShapeModule::getDirectionInHemisphereMode() 
{
	// enforce to generate direction be included in hemisphere
	// 利用eulerangle将transform.up向量旋转得到新的半球
	return Vector3::up;
}
Vector3 ParticleShapeModule::getDirectionInConeMode() 
{
	return Vector3::up;
}
Vector3 ParticleShapeModule::getDirecitonInRectangleMode() 
{
	return Vector3::up;
}

#pragma endregion