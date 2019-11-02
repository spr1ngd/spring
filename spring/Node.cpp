#include "node.h"
#include "transform.h"

using namespace std;
using namespace spring;

Node::Node() 
{
	this->transform = new Transform();
}

Node::Node(const char* nodeName) 
{
	this->name = nodeName;
	this->transform = new Transform();
}

template <typename T>
Node* Node::AddNode()
{
	T* instance = new T();
	this->nodes.push_back((Node*)instance);
	return (Node*)instance;
}

template <typename T>
Node* Node::GetNode(T nodeType) 
{
	for (Node* node :this->nodes)
	{
		if (typeid(node).name() == typeid(nodeType).name()) 
		{
			return node;
		}
	}
	return nullptr;
}

template <typename T>
bool Node::TryGetNode( T nodeType ,Node* node)
{
	Node* node = nullptr;
	node = this->GetNode(nodeType);
	return node != nullptr;
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