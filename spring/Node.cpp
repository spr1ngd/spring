#include "node.h"
#include "transform.h"
#include "console.h"
#include "misc.h"
#include "scene.h"

using namespace std;
using namespace spring;

vector<Node*> Node::allNodes;

Node::Node() 
{
	this->type = "Node";
	this->transform = new Transform();
	allNodes.push_back(this);
	this->name = "Node(Instance)";
	if (nullptr != Scene::current)
		Scene::current->AddNode(this);
}

Node::Node(const char* nodeName) 
{
	this->type = "Node";
	this->name = nodeName;
	this->transform = new Transform();
	allNodes.push_back(this);
	if (nullptr != Scene::current)
		Scene::current->AddNode(this);
}

Node::~Node() 
{
	for (auto it = allNodes.begin(); it != allNodes.end(); it++) 
	{
		Node* node = *it;
		if (node == this)
		{
			PRINT_ERROR("destroy node %s", node->name);
			Scene::current->RemoveNode(this);
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
	Scene::current->RemoveNode(this);
	this->parent = node;
	node->children.insert(node->children.end(), this);
}

#pragma region static methods 

Node* Node::Query(const char* name) 
{
	for (vector<Node*>::iterator item = allNodes.begin(); item != allNodes.end(); item++) 
	{
		Node* node = *item;
		if (node->name == name)
			return node;
	}
	return nullptr;
}

#pragma endregion static methods 