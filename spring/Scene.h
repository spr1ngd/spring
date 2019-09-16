#pragma once

namespace spring 
{
	class Scene 
	{
	public:
		const char* name;
	public:
		static void LoadScene(Scene* scene);
		static void UnloadScene(Scene* scene);
		static Scene* ReadScene(const char* scenePath);
		static void SaveScene(const char* scenePath,Scene*scene);
	};
}