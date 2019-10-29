#pragma once
#include "uielement.h"

namespace spring 
{
	namespace ui 
	{
		class Image : public UIElement
		{
		protected:
		public:
			virtual void GenerateMesh();
			Image();
			void Render() override;
		};
	}
}