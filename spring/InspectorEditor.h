#pragma once

#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class InspectorEditor : EditorWindow
		{
		protected:
			virtual void OnDrawInspector();

			void Show() override;
			void Hide() override;
			void OnDrawWindow() override;

		public:
			InspectorEditor(const char* name,bool openDefault = true);
		};
	}
}