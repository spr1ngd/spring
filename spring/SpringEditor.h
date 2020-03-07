#pragma once
#include "guilayout.h"
#include "editorwindow.h"
#include "inspectorwindow.h"
#include "hierarchywindow.h"
#include "scenewindow.h"
#include "inspectoreditor.h"
#include "menuwindow.h"
#include "selection.h"

namespace spring
{
	namespace editor 
	{
		class SpringEditor
		{
		private:
			static InspectorWindow* inspector;
			static HierarchyWindow* hierarchy;
			static SceneWindow* scene;
			static MenuWindow* menu;
		public:
			static bool enabled;
			static void Initialize();
			static void Release();

			static void DrawEditor();
		};
	}
}