#include "layer.h"

using namespace std;
using namespace spring;

LayerMask::LayerMask() 
{
	this->add(Layer::Default);
	this->add(Layer::UI);
}

void LayerMask::set(unsigned int layers[]) 
{
	this->layers.clear();
	for (int i = 0; i < sizeof(layers); i++)
		this->add(layers[i]);
}

void LayerMask::add(unsigned int layer) 
{
	if (!this->contains(layer))
		this->layers.push_back(layer);
}

void LayerMask::remove(unsigned int layer) 
{
	for (vector<unsigned int>::iterator l = this->layers.begin(); l != this->layers.end(); l++) 
	{
		if (*l == layer) 
		{
			this->layers.erase(l);
			return;
		}
	}
}

bool LayerMask::contains(unsigned int layer) 
{
	for (auto l : this->layers)
	{
		if (l == layer)
			return true;
	}
	return false;
}