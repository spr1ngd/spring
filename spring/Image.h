#pragma once
#include "uielement.h"

namespace spring 
{
	namespace ui 
	{
		class Image : public UIElement
		{
		protected:
			Image();
			virtual void GenerateMesh();
		public:
			void Render() override;
		};
	}
}