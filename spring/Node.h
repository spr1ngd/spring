#pragma once
#include "object.h"
#include <vector>

using namespace std;

namespace spring 
{ 
	class Node : public Object
	{
	private:
		vector<Node> nodes;
	public:
		bool enable;
		Node* parent;
		vector<Node> children;
		// todo : add a new field Transform transform;?????
		
	public:
		Node();
		Node( const char*nodeName );
		template <typename T>
		Node* GetNode(T nodeType);
		template <typename T>
		bool TryGetNode(T nodeType,Node* node);

		Node* GetChild(const char*nodeName);
		void SetParent(const Node node); 

		static Node* Instantiate(Node node);
		static void Destroy();
	};
}