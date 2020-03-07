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
	private:
		vector<Node*> nodes;
	public:
		bool visible = true;
		Layer layer = Layer::Default;

		Node* parent;
		vector<Node*> children;
		Transform* transform;
		
	protected:
		Node();
		Node( const char*nodeName );

	public:
		~Node();

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