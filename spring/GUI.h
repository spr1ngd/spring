#pragma once
#include <vector>
#include "springengine.h"

namespace spring 
{
	namespace ui 
	{
		class GUI 
		{
		private:
			static std::vector<UIElement&> uiElements;
		public:
			static Image& DrawImage(Rect& rect);
		};
	}
}
