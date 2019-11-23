#pragma once

namespace spring
{
	class UniformBuffer
	{
	private:
		unsigned int buffer;

	public:

		UniformBuffer(unsigned int size,unsigned int drawMode = 35044);
		void BindSubData( unsigned int index,unsigned int size, const void* data);
		void BlockBinding(const unsigned int gpuProgram,const char* blockName ,const unsigned int bindingPoint);
	};
}