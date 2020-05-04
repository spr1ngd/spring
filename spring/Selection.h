#pragma once
#include <functional>
#include <vector>
#include "gameobject.h"

namespace spring 
{
	namespace editor 
	{
		class Selection 
		{
		private:
			static GameObject* gameobject;
			static std::vector<std::function<void(GameObject&)>> onSelectEvents;
			static std::vector<std::function<void(GameObject&)>> onDeselectEvents;
		public:

			static void OnSelect(std::function<void(GameObject&)> selectEvent);
			static void OnDeselect(std::function<void(GameObject&)> deselectEvent);

			static void Select(GameObject* target);
			static GameObject* GetSelected();
		};
	}
}