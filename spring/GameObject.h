#pragma once

#include <vector>
#include <string>
#include "scene.h"
#include "object.h"
#include "transform.h"

using namespace std;

namespace spring 
{
	enum HideFlags 
	{
		HideFlags_None = 0x00000000,
		HideFlags_HideInHierarchyWindow = 0x00000001,
		HideFlags_NotEditable = 0x00000010
	};

	class GameObject : public Object
	{
	private:
		static std::vector<GameObject*> gameobjects;

		static void AddGameObject(GameObject* gameobject);
		static void RemoveGameObject(GameObject* gameobject);

		bool visible = true;
		int flags = 0x00000000;
	public:
		int layer = 0x00000001;
		Transform* transform; // only store position/rotation/scale/eulerangle data

		std::vector<Node*> nodes;
		GameObject* parent;
		std::vector<GameObject*> children;

		GameObject();
		GameObject(const char* name);
		~GameObject() override;

		template<typename T>
		T* AddNode() 
		{
			T* node = new T();
			this->nodes.push_back(node);
			Node* nodeptr = dynamic_cast<Node*>(node);
			nodeptr->gameobject = this;
			nodeptr->name = this->name;
			delete nodeptr->transform;
			nodeptr->transform = this->transform;
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

		template<typename T>
		std::vector<T*> GetNodesInChildren()
		{
			std::vector<T*> result;
			for (auto child = this->children.begin(); child != children.end(); child++)
			{
				GameObject* childPtr = *child;
				T* node = childPtr->GetNode<T>();
				result.push_back(node);
				std::vector<T*> resultInChildren = childPtr->GetNodesInChildren<T>();
				result.insert(result.end(), resultInChildren.begin(), resultInChildren.end());
			}
			return result;
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

		void SetActive(bool visible);
		bool GetActive();

		inline bool HasFlag( HideFlags hideFlag ) 
		{
			return (this->flags & hideFlag) == hideFlag;
		}
		inline void SetFlag(HideFlags hideFlag)
		{
			this->flags |= hideFlag;
		}
		inline void RemoveFlag(HideFlags hideFlag) 
		{
			this->flags &= ~hideFlag;
		}

		TypeInfo GetTypeInfo() override 
		{
			if (nullptr == this->typeInfo)
				this->typeInfo = new TypeInfo("GameObject");
			return *this->typeInfo;
		}
		void Destroy() override;

	public:
		static GameObject* Query(const char* name) 
		{
			for (auto item = gameobjects.begin(); item != gameobjects.end(); item++) 
			{
				GameObject* gameobject = *item;
				if (strcmp(gameobject->name, name) == 0) 
					return *item;
			}
			return nullptr;
		}

		static void Destroy(GameObject* gameobject) 
		{
			gameobject->Destroy();
		}
	};
}