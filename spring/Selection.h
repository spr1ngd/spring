#pragma once
#include <functional>
#include "node.h"
typedef void (*SelectionChanged)();

namespace spring 
{
	namespace editor 
	{
		class Selection 
		{
		public:
			static Node* node;
			static Node* nodes;
			static SelectionChanged selectionChanged;

			static void Select(Node* node);
			static void Unselect(Node* node);
		};
	}
}