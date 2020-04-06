#pragma once
#include "inspectoreditor.h"

namespace spring 
{
	namespace editor 
	{
		class GameObjectEditor : public InspectorEditor 
		{
		public:
			GameObjectEditor(const char* name, const char* type, bool openDefault = true) : InspectorEditor(name, type, openDefault) {}

			void OnDrawInspector() override;
		};
	}
}