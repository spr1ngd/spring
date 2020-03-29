#pragma once
#include <vector>

using namespace std;

namespace spring 
{
	enum Layer 
	{
		None = 0x00000000,
		Default = 0x00000001,
		UI = 0x00000010,
		Skybox = 0x00000100,
		PostProcessing = 0x00001000,
		Everything = 0x11111111
	};

	class LayerMask // replaced use bit operation.
	{
	private:
		vector<unsigned int> layers;

	public:
		Layer layer;
		LayerMask();

		void set(unsigned int layers[]);
		void add(unsigned int layer);
		void remove(unsigned int layer);
		bool contains(unsigned int layer);
	};
}