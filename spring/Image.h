#pragma once
#include "uielement.h"
#include "texture.h"

namespace spring 
{
	namespace ui 
	{
		class Image : public UIElement
		{
		public:
			Texture* texture;
		public:
			Image();
			virtual void GenerateMesh();
			void Render() override;
		};
	}
}