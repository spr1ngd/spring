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
		public:
			class RichText
			{
			public:
				Character* character;
				Color color;
				float size;
				bool isTag = false;
				bool bold = false;
				bool strike = false;
				bool underline = false;
				bool isImage = false;
				bool italic = false;
				bool anchor = false;

				RichText();
			};

		private:
			const char* htmlTags[8] = {"color","size","b","s","u","image","i","a"};
			string text;

			string* parseTags(string text);
		public:
			Font* font;
			bool richText = false;
			float characterSpace = 0.0f;

		public:
			Text();

			void SetText(string text);
			string GetText();

			void GenerateMesh() override;
			void Render() override;
		};
	}
}