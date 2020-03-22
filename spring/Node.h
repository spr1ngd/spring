#pragma once
#include <vector>
#include "layer.h"
#include "object.h"
#include "transform.h"

using namespace std;

namespace spring 
{ 
	class Node : public Object
	{
	public:
		static vector<Node*> allNodes;

		bool visible = true;
		Layer layer = Layer::Default;
		Node* parent;
		vector<Node*> nodes;
		vector<Node*> children;
		Transform* transform;
		
		Node();
		Node(const char* nodeName);
		~Node();

		// query node object by name in current scene. if have return node* ,if not return nullptr.
		static Node* Query(const char* name);

		template <typename T>
		Node* GetNode(T nodeType) 
		{
			for (Node* node : this->nodes)
			{
				if (typeid(node).name() == typeid(nodeType).name())
					return node;
			}
			return nullptr;
		}

		template <typename T>
		bool TryGetNode(T nodeType, Node* node) 
		{
			Node* node = nullptr;
			node = this->GetNode(nodeType);
			return node != nullptr;
		}

		template <typename T>
		Node* AddNode()
		{
			T* instance = new T();
			this->nodes.push_back((Node*)instance);
			return (Node*)instance;
		}

		Node* GetChild(const char*nodeName);
		void SetParent(Node* node);
	};
}