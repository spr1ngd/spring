#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class HierarchyWindow : public EditorWindow
		{
		public:
			HierarchyWindow(const char* name, bool openDefault);

			void OnDrawWindow() override;
		};
	}
}