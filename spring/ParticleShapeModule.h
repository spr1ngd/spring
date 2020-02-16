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

		struct HemisphereProperty 
		{
			float radius = 1.0f;
		};

		struct ConeProperty 
		{
			float bottomRadius = 1.0f;
			float topRadius = 1.0f;
			float height = 1.0f;
		};
		
		struct RectangleProperty
		{
			float length = 1.0f;
			float width = 1.0f;
		};

		Transform* transform;
		ShapeType shapeType = Cube;
		// cube properties
		CubeProperty cubeProperties;
		// sphere properties
		SphereProperty sphereProperties;
		// hemisphere properties
		HemisphereProperty hemisphereProperties;
		// cone properties
		ConeProperty coneProperties;
		// rectangle properties
		RectangleProperty rectangleProperties;

		ParticleShapeModule();
		ParticleShapeModule(Transform* transform);
		void getSrcParticle(Vector3& position,Vector3& direction);

	private:
		Vector3 getDirection();
		Vector3 getDirectionInCubeMode();
		Vector3 getDirectionInSphereMode();
		Vector3 getDirectionInHemisphereMode();
		Vector3 getDirectionInConeMode(Vector3 emitPos);
		Vector3 getDirecitonInRectangleMode();

		Vector3 getSrcPosition();
		Vector3 getSrcPositionInCubeMode();
		Vector3 getSrcPositionInSphereMode();
		Vector3 getSrcPositionInHemisphereMode();
		Vector3 getSrcPositionInConeMode();
		Vector3 getSrcPositionInRectangleMode();
	};
}
