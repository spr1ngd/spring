#pragma once
#include "inspectoreditor.h"

namespace spring 
{
	namespace editor 
	{
		class TransformEditor : public InspectorEditor
		{
		public:
			TransformEditor(const char* name, const char* type, bool openDefault = true) :InspectorEditor(name, type, openDefault) {}

			void OnDrawInspector() override;
		};
	}
}