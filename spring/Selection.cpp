#include "selection.h"

using namespace spring;
using namespace spring::editor;

GameObject* Selection::gameobject;
std::vector<std::function<void(GameObject&)>> Selection::onSelectEvents;
std::vector<std::function<void(GameObject&)>> Selection::onDeselectEvents;

void Selection::Select(GameObject* target)
{
	if (gameobject == target)
		return;
	if (nullptr != gameobject)
	{
		for (const auto& deselect : onDeselectEvents)
			deselect(*gameobject);

	}
	for (const auto& select : onSelectEvents)
		select(*target);
	gameobject = target;
}

GameObject* Selection::GetSelected() 
{
	return Selection::gameobject;
}

void Selection::OnSelect(std::function<void(GameObject&)> selectEvent)
{
	onSelectEvents.push_back(selectEvent);
}

void Selection::OnDeselect(std::function<void(GameObject&)> deselectEvent) 
{
	onDeselectEvents.push_back(deselectEvent);
}