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
	this->transform = new Transform();
	allNodes.push_back(this);
	this->name = misc::gen_guid();
	Console::LogFormat("instantiate node %s",this->name);
	Scene::current->AddNode(this);
}

Node::Node(const char* nodeName) 
{
	this->name = nodeName;
	this->transform = new Transform();
	allNodes.push_back(this);
	Console::LogFormat("instantiate node %s", nodeName);
	Scene::current->AddNode(this);
}

Node::~Node() 
{
	for (auto it = allNodes.begin(); it != allNodes.end(); it++) 
	{
		Node* node = *it;
		if (node == this)
		{
			Console::ErrorFormat("destroy node %s", node->name);
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
	node->parent = this;
	this->children.insert(this->children.end(), node);
}