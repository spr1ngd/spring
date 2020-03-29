#pragma once
#include "springengine.h"

namespace spring
{
	class FullScreenRenderer : public MeshRenderer
	{
	public:
		FullScreenRenderer();
		void Initialize() override;
	};
}