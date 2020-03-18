#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class SceneWindow : public EditorWindow
		{
		protected:
			void BeginWindow() override;

		public:
			SceneWindow(const char* name, bool defaultOpen);
			void OnDrawWindow() override;
		};
	}
}