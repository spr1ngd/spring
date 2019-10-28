#pragma once
#include <vector>
#include "object.h"
#include "transform.h"

using namespace std;

namespace spring 
{ 
	class Node : public Object
	{
	private:
		vector<Node*> nodes;
	public:
		bool enable;
		Node* parent;
		vector<Node> children;
		Transform* transform;
		
	protected:
		Node();
		Node( const char*nodeName );

	public:
		template <typename T>
		Node* GetNode(T nodeType);

		template <typename T>
		bool TryGetNode(T nodeType,Node* node);

		template <typename T>
		Node* AddNode();

		Node* GetChild(const char*nodeName);
		void SetParent(const Node node); 
		static Node* Instantiate(Node node);
		static void Destroy();
	};
}