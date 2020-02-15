#include "particleshapemodule.h"

using namespace spring;

ParticleShapeModule::ParticleShapeModule() 
{
	this->shapeType = ShapeType::Cube;
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
	return Vector3::zero;
}
Vector3 ParticleShapeModule::getSrcPositionInSphereMode()
{
	return Vector3::zero;
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
	return Vector3::up;
}
Vector3 ParticleShapeModule::getDirectionInSphereMode() 
{
	return Vector3::up;
}
Vector3 ParticleShapeModule::getDirectionInHemisphereMode() 
{
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