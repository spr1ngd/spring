#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class InspectorWindow : public EditorWindow
		{
		public:
			InspectorWindow(const char* name, bool openDefault);
			void OnDrawWindow() override;
		};
	}
}