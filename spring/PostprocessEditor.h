#pragma once

#include "inspectoreditor.h"

namespace spring 
{
	namespace editor
	{
		class PostprocessEditor : InspectorEditor
		{
		protected:
			void OnDrawInspector() override;
		public:
			PostprocessEditor(const char* name,bool openDefault = true);
		};
	}
}