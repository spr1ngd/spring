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
	allNodes.push_back(this);
	this->name = "Node(Instance)";
	if (nullptr != Scene::current)
		Scene::current->AddNode(this);
}

Node::Node(const char* nodeName) 
{
	PRINT_ERROR("Can not allow to construct node throught with name");
	this->type = "Node";
	this->name = nodeName;
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

void Node::Destroy() 
{
	delete this;
}