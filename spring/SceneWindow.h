#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class SceneWindow : public EditorWindow
		{
		public:
			SceneWindow(const char* name, bool defaultOpen) : EditorWindow(name, defaultOpen) {}

			void OnDrawWindow() override;
		};
	}
}