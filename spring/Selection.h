#pragma once
//#include "springengine.h"
#include <functional>

typedef void (*SelectionChanged)();

namespace spring 
{
	namespace editor 
	{
		class Node;
		class Selection 
		{
		private:
		public:
			static Node* node;
			static Node* nodes;
			static SelectionChanged selectionChanged;

			static void Select(Node* node);
			static void Unselect(Node* node);
		};
	}
}