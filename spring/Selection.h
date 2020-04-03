#pragma once
#include <functional>
#include "node.h"
#include "gameobject.h"

typedef void (*SelectionChanged)();

namespace spring 
{
	namespace editor 
	{
		class Selection 
		{
		public:
			static GameObject* gameobject;
			static Node* node;
			static Node* nodes;
			static SelectionChanged selectionChanged;

			static void Select(Node* node);
			static void Unselect(Node* node);
		};
	}
}