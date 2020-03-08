#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class StatusWindow : public EditorWindow
		{
		public:
			StatusWindow(const char* name, bool openDefault = false);

			void OnDrawWindow() override;
		};
	}
}