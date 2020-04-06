
#pragma once
#include "inspectoreditor.h"

namespace spring
{
	namespace editor
	{
		class MaterialEditor : public InspectorEditor
		{
		public:
			MaterialEditor(const char* name, const char* type, bool defaultOpen = true) : InspectorEditor(name, type, defaultOpen) {}

			void OnDrawInspector() override;
		};
	}
}