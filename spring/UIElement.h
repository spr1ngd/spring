#pragma once
#include "color.h"
#include "rect.h"
#include "recttransform.h"
#include "meshrenderer.h"

namespace spring 
{
	namespace ui 
	{
		class UIElement : public MeshRenderer
		{
		public:
			RectTransform* rectTransform;
			Color color = Color::white;
		public:
			UIElement();

			void Render() override;
		};
	}
}