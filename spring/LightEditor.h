#pragma once 
#include "inspectoreditor.h"

namespace spring 
{
	namespace editor 
	{
		class LightEditor : public InspectorEditor 
		{
		public:
			LightEditor(const char* name, const char* type, bool openDefault = true) :InspectorEditor(name, type, openDefault) {}

			void OnDrawInspector() override;
		};
	}
}