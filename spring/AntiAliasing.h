#pragma once

namespace spring 
{
	class AntiAliasing
	{
	public:
		bool enabled = false;
		unsigned int samples = 0;

		AntiAliasing();
	};
}