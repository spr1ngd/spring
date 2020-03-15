#pragma once
#include "springengine.h"
#include <functional>
#include <map>

namespace spring
{
	class Picking
	{
		// todo : generate a color framebuffer
		// todo : draw all objects per frame to this framebuffer
		// todo : convert renderable object identify to color
		// todo : convert color to identify 
		// todo : glReadPixel
	public:
		static bool enable;

		static FrameBuffer* colorbuffer;
		static Material* material;
		static void Initialize();
		static Node* Pick(unsigned int x, unsigned int y);
		static Colorf Convert2Color(unsigned int identify);
		static unsigned int Convert2Identify(Colorf color);
		static void Render(std::function<void()> func);
		Picking();
	};
}