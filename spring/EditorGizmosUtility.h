#pragma once
#include "gameobject.h"

namespace spring
{
	namespace editor 
	{
		class EditorGizmosUtility 
		{
		private:
			static void DrawAxis(GameObject& target);
		public:
			// draw the xyz coordinate axis
			static void Initialize();
		};
	}
}