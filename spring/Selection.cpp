#include "selection.h"

using namespace spring;
using namespace spring::editor;

GameObject* Selection::gameobject = nullptr;
Node* Selection::node = nullptr;
Node* Selection::nodes = nullptr;

void Selection::Select(Node* node) 
{
	// selectionChanged();
	node = node;
}

void Selection::Unselect(Node* node) 
{
	// 
}