#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class MenuWindow : public EditorWindow
		{
		public:
			MenuWindow(const char* name, bool defaultOpen);

			void BeginWindow() override;
			void EndWindow() override;
			void OnDrawWindow() override;
		};
	}
}