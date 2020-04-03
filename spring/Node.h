#pragma once
#include <vector>
#include "layer.h"
#include "object.h"
#include "transform.h" // todo 将transform移动到gameobject节点
#include "gameobject.h"

using namespace std;

namespace spring 
{ 
	enum NodeFlags 
	{
		BuiltIn = -1, // all built-in nodes are generated by spring engine , these objects provide functionality for editor scene. those objects does not need add into scene.
		Static = 0,  // all static nodes are created in editor mode , those nodes would serialize into scene data.
		Dynamic = 1,  // all dynamic nodes would not be serialized into scene data
	};

	class Node : public Object
	{
	public:
		static vector<Node*> allNodes;

		bool visible = true;
		Layer layer = Layer::Default;
		NodeFlags flags = NodeFlags::Dynamic;
		Node* parent = nullptr;
		vector<Node*> nodes;
		vector<Node*> children;

		Transform* transform;
		GameObject* gameobject;
		
		Node();
		Node(const char* nodeName);
		~Node();

		// query node object by name in current scene. if have return node* ,if not return nullptr.
		static Node* Query(const char* name);

		template <typename T>
		T* GetNode() 
		{
			for (Node* node : this->nodes)
			{
				const char* queryTypeName = typeid(T).name();
				if (strcmp(node->type,queryTypeName) == 0)
					return (T*)node;
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
		T& AddNode()
		{
			T* node = new T();
			this->nodes.push_back(node);
			return *node;
		}

		template <typename T>
		void AddNode(T& node)
		{
			this->nodes.push_back(&node);
		}


		Node* GetChild(const char* nodeName);
		void SetParent(Node* node);

		TypeInfo GetTypeInfo() override
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("Node");
			return *this->typeInfo;
		}
	};
}