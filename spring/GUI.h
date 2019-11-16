#pragma once
#include <vector>
#include "rect.h"
#include "uielement.h"
#include "image.h"
#include "text.h"

namespace spring 
{
	namespace ui 
	{
		class GUI 
		{
		private:
			static std::vector<UIElement*> uiElements;
		public:
			static Image* DrawImage(Rect rect);
			static Text* DrawText(Rect rect);
		};
	}
}
