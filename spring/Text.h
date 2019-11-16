#pragma once
#include "uielement.h"
#include <string>
#include "font.h"

namespace spring
{
	namespace ui 
	{
		class Text : public UIElement
		{
		private:
			string text;
		public:
			Font* font;

		public:
			Text();

			void SetText(string text);
			string GetText();

			void GenerateMesh() override;
			void Render() override;
		};
	}
}