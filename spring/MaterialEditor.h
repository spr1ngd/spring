
#pragma once
#include "inspectoreditor.h"

namespace spring
{
	namespace editor
	{
		class MaterialEditor : public InspectorEditor
		{
		protected:
			void OnDrawInspector() override;
		public:
			MaterialEditor(const char* windowName, bool defaultOpen = true);
		};
	}
}