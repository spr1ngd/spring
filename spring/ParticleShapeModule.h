#pragma once
#include "springengine.h"

namespace spring 
{
	class ParticleShapeModule
	{
	public:
		enum ShapeType
		{
			Cone,
			Cube,
			Sphere,
			Hemishpere,
			Rectangle
		};

		struct CubeProperty 
		{
			float size = 1.0f;
		};

		struct SphereProperty
		{
			float radius = 1.0f;
		};

		struct ConeProperty 
		{
			float radius = 1.0f;
			float angle = 60.0f;
		};
		
		struct RectangleProperty
		{
			float length = 1.0f;
			float width = 1.0f;
		};

		ShapeType shapeType = Cube;
		
		// cube properties
		CubeProperty cubeProperties;
		// sphere properties
		SphereProperty sphereProperties;
		// cone properties
		ConeProperty coneProperties;
		// rectangle properties
		RectangleProperty rectangleProperties;

		ParticleShapeModule();
		Vector3 getDirection();
		Vector3 getSrcPosition();

	private:
		Vector3 getDirectionInCubeMode();
		Vector3 getDirectionInSphereMode();
		Vector3 getDirectionInHemisphereMode();
		Vector3 getDirectionInConeMode();
		Vector3 getDirecitonInRectangleMode();

		Vector3 getSrcPositionInCubeMode();
		Vector3 getSrcPositionInSphereMode();
		Vector3 getSrcPositionInHemisphereMode();
		Vector3 getSrcPositionInConeMode();
		Vector3 getSrcPositionInRectangleMode();
	};
}
