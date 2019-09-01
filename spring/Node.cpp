#include "node.h"

using namespace std;
using namespace spring;

Node::Node() 
{

}

template <typename T>
Node* Node::GetNode(T nodeType) 
{
	for (Node &node :this->nodes)
	{
		if (typeid(node).name() == typeid(nodeType).name()) 
		{
			return &node;
		}
	}
	return nullptr;
}

template <typename T>
bool Node::TryGetNode( T nodeType ,Node* node)
{

}

Node* Node::GetChild(const char* nodeName) 
{
	for (Node &node : this->children)
	{
		if (node.name == nodeName)
			return &node;
	}
	return nullptr;
}

void Node::SetParent(Node node) 
{
	// todo : if node is null , what should i do ?
	node.parent = this;
	this->children.insert(this->children.end(), node);
}

Node Node::Instantiate(Node node) 
{

}

void Node::Destroy()
{
	//todo : remove from node tree.
}