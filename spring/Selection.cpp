#include "selection.h"

using namespace spring;
using namespace spring::editor;

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