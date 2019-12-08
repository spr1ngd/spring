#pragma once
#include <vector>

namespace spring
{
	namespace editor 
	{
		class EditorWindow 
		{
		private:
			static std::vector<EditorWindow*> editorWindows;
			const char* name;
			bool enabled = true;

			void BeginWindow();
			void EndWindow();
		public:
			EditorWindow(const char*name, bool openDefault = true);

			virtual void Show();
			virtual void Hide();
			virtual void OnDrawWindow();

			static EditorWindow* OpenWindow(const char* name,bool openDefault = true);
			static void CloseWindow(EditorWindow* window);
			static void CloseWindow(const char* name);
			static void RenderWindows();
		};
	}
}