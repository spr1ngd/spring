#pragma once
#include "behaviour.h"

namespace spring
{ 
	namespace editor
	{
		class EditorApplication : public Behaviour
		{ 
		public:

			void Awake() override;
			void Update() override;
			void Destroy() override;
		};
	}
}