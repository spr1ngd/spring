#pragma once

#include <vector>
#include <string>
#include "scene.h"
#include "object.h"
#include "transform.h"

using namespace std;

namespace spring 
{
	class GameObject : public Object
	{
	private:
		static std::vector<GameObject*> gameobjects;

		static void AddGameObject(GameObject* gameobject);
		static void RemoveGameObject(GameObject* gameobject);

	private:
		std::vector<Node*> nodes;

	public:
		bool visible = true;
		Transform transform; // only store position/rotation/scale/eulerangle data

		GameObject* parent;
		std::vector<GameObject*> children;

		GameObject();
		GameObject(const char* name);

		template<typename T>
		T* AddNode() 
		{
			T* node = new T();
			this->nodes.push_back(node);
			Node* nodeptr = dynamic_cast<Node*>(node);
			nodeptr->gameobject = this;
			return node;
		}

		template<typename T>
		T* GetNode() 
		{
			const char* queryTypeName = typeid(T).name();
			
			std::string queryType = string(queryTypeName);
			auto lastIndex = queryType.find_last_of(":");
			auto className = queryType.substr(lastIndex + 1,64);
			for (auto node = this->nodes.begin(); node != nodes.end(); node++) 
			{
				Node* nodeptr = *node;
				std::string nodeType = nodeptr->GetTypeInfo().typeName;
				if (className.compare(nodeType) == 0)
				{
					T* result = dynamic_cast<T*>(*node);
					return result;
				}
			}
			return nullptr;
		}

		void SetParent( GameObject* newParent ) 
		{
			if (this->parent == newParent)
				return;
			if (nullptr == this->parent && nullptr != newParent)
				Scene::current->RemoveGameObject(this);
			if (nullptr != this->parent) 
			{
				for (auto child = this->parent->children.begin(); child != this->parent->children.end(); child++) 
				{
					if (*child == this)
					{
						this->parent->children.erase(child);
						this->parent = nullptr;
						continue;
					}
				}
			}
			if (nullptr == newParent) 
			{
				Scene::current->AddGameObject(this);
			}
			else 
			{
				this->parent = newParent;
				newParent->children.push_back(this);
			}
		}

		GameObject* GetChild( int childIndex ) 
		{
			if (childIndex >= this->children.size())
				return nullptr;
			return this->children[childIndex];
		}

		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("GameObject");
			return *this->typeInfo;
		}
	};
}