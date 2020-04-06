#pragma once
#include <map>
#include "editorwindow.h"
#include "inspectoreditor.h"

namespace spring 
{
	namespace editor 
	{
		class InspectorWindow : public EditorWindow
		{
		private:
			static std::map<const char*, InspectorEditor*> editors;

		public:
			InspectorWindow(const char* name, bool openDefault);
			void OnDrawWindow() override;

			static void AddInspectorEditor(InspectorEditor* inspectorEditor) 
			{
				auto item = editors.find(inspectorEditor->editorName);
				if (item != editors.end())
					return;
				editors.insert(std::pair<const char*, InspectorEditor*>(inspectorEditor->editorName, inspectorEditor));
			}
		};
	}
}