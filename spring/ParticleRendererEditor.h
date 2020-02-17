#pragma once

#include "inspectoreditor.h"

namespace spring 
{
	namespace editor
	{
		class ParticleRendererEditor : InspectorEditor
		{
		protected:
			void OnDrawInspector() override;

		public:
			ParticleRendererEditor(const char* name,bool openDefault = true);
		};
	}
}