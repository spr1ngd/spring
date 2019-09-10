#pragma once

namespace spring 
{
	class Renderable 
	{
	public:
		// todo : record all renderable object , when spring engine running , render objects in fixed sequence with model's layer.
		virtual void Render() = 0;
	};
}