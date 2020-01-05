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
		bool visible;
		Layer layer = Layer::Default;

		Node* parent;
		vector<Node> children;
		Transform* transform;
		
	protected:
		Node();
		Node( const char*nodeName );

	public:
		~Node();

		template <typename T>
		Node* GetNode(T nodeType);

		template <typename T>
		bool TryGetNode(T nodeType,Node* node);

		template <typename T>
		Node* AddNode();

		Node* GetChild(const char*nodeName);
		void SetParent(const Node node);
	};
}