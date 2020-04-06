#pragma once
#include "editorwindow.h"

namespace spring 
{
	namespace editor 
	{
		class InspectorEditor
		{
		public:
			const char* editorName;
			const char* editorType;
			bool openDefault = true;
			InspectorEditor(const char* editorName,const char* editorType,bool openDefault = true);

			virtual void OnDrawInspector();
		};
	}
}