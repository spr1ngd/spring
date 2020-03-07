#include "node.h"
#include "transform.h"

using namespace std;
using namespace spring;

vector<Node*> Node::allNodes;

Node::Node() 
{
	this->transform = new Transform();
	allNodes.push_back(this);
	
}

Node::Node(const char* nodeName) 
{
	this->name = nodeName;
	this->transform = new Transform();
	allNodes.push_back(this);
}

Node::~Node() 
{
	// todo : recalculate node's hierarchy relationship
	for (auto it = allNodes.begin(); it != allNodes.end(); it++) 
	{
		if (*it == this)
		{
			allNodes.erase(it);
			break;
		}
	}
}

Node* Node::GetChild(const char* nodeName) 
{
	for (Node* node : this->children)
	{
		if (node->name == nodeName)
			return node;
	}
	return nullptr;
}

void Node::SetParent(Node* node) 
{
	node->parent = this;
	this->children.insert(this->children.end(), node);
}