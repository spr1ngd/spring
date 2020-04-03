#include "particleshapemodule.h"

using namespace spring;

ParticleShapeModule::ParticleShapeModule() 
{

}

ParticleShapeModule::ParticleShapeModule(Transform* transform) 
{
	this->transform = transform;
}

void ParticleShapeModule::getSrcParticle(Vector3& position, Vector3& direction) 
{
	if (this->shapeType == ShapeType::Cone) 
	{
		Vector3 bottomPos = Vector3(
			Mathf::Randomf(-this->coneProperties.bottomRadius, this->coneProperties.bottomRadius),
			0.0f,
			Mathf::Randomf(-this->coneProperties.bottomRadius, this->coneProperties.bottomRadius));
		direction = this->getDirectionInConeMode(bottomPos);
		position = bottomPos;
	}
	else
	{
		position = this->getSrcPosition();
		direction = this->getDirection();
	}
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
		PRINT_ERROR("[spring.particlerenderer] : invalid shape type [%s]", this->shapeType);
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
	return this->transform->position;
}
Vector3 ParticleShapeModule::getSrcPositionInHemisphereMode()
{
	return this->transform->position;
}
Vector3 ParticleShapeModule::getSrcPositionInConeMode() 
{
	return Vector3::zero;
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
	//case ShapeType::Cone:
		//return this->getDirectionInConeMode();
	case ShapeType::Rectangle:
		return this->getDirecitonInRectangleMode();
	default:
		PRINT_ERROR("[spring.particlerenderer] : invalid shape type [%s]",this->shapeType);
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
Vector3 ParticleShapeModule::getDirectionInConeMode( Vector3 emitPos ) 
{
	Vector3 dir = Vector3::Normalize(emitPos);
	Vector3 topPos = dir * this->coneProperties.topRadius;
	topPos += Vector3(0.0f,this->coneProperties.height,0.0f);
	return Vector3::Normalize(topPos - emitPos);
}
Vector3 ParticleShapeModule::getDirecitonInRectangleMode() 
{
	return this->transform->up;
}

#pragma endregion