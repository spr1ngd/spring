#pragma once
#include "springengine.h"
#include <functional>
#include <map>

namespace spring
{
	class Node;
	class GameObject;
	class Picking
	{
	public:
		static bool enable;
		static GameObject* selected;
		static FrameBuffer* pickBuffer;
		static Material* material;

		static void Initialize();
		static void Pick();
		static Node* Pick(unsigned int x, unsigned int y);
		static Colorf Convert2Color(unsigned int identify);
		static unsigned int Convert2Identify(Colorf color);
		static unsigned int Convert2Identify(Color color);
		static void Render(std::function<void()> func);
		Picking();
	};
}