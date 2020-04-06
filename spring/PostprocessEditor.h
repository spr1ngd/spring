#pragma once
#include "inspectoreditor.h"

namespace spring 
{
	namespace editor
	{
		class PostprocessEditor : public InspectorEditor
		{
		public:
			PostprocessEditor(const char* name, const char* type, bool openDefault = true) :InspectorEditor(name, type, openDefault) {}

			void OnDrawInspector() override;
		};
	}
}