#pragma once

#include "inspectoreditor.h"

namespace spring 
{
	namespace editor
	{
		class ParticleRendererEditor : InspectorEditor
		{
		public:
			ParticleRendererEditor(const char* name, const char* type, bool openDefault = true) :InspectorEditor(name, type, openDefault) {}

			void OnDrawInspector() override;
		};
	}
}