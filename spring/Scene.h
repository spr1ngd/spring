#pragma once
#include <map>
#include "node.h"

namespace spring 
{
	class Scene 
	{
	public:
		static std::map<const char*, Scene*> scenes;
		static Scene* current;

		static void Load(const char* sceneName);
		static void Unload(const char* sceneName);
		static Scene* ReadScene(const char* scenePath);
		static void SaveScene(const char* scenePath,Scene*scene);
		static void AddScene(Scene* scene);
		static void RemoveScene(Scene* scene);

		// interfaces about scene object
	public:
		const char* name;
		std::map<const char*, Node*> nodes;

		Scene(const char* name);
		void AddNode(Node* node);
		void RemoveNode(Node* node);
	};
}