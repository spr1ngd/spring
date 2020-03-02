#pragma once

#include "inspectoreditor.h"

namespace spring
{
	namespace editor 
	{
		class PickingEditor : public InspectorEditor
		{
		protected:
			void OnDrawInspector() override;
		public:
			PickingEditor(const char* windowName,bool openDefault = true);
		};
	}
}