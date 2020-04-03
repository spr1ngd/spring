#include "layer.h"

using namespace std;
using namespace spring;

LayerMask::LayerMask() 
{ 

}

void LayerMask::set(int layers) 
{
	this->layers = layers;
}

void LayerMask::add(unsigned int layer) 
{
	this->layers |= layer;
}

void LayerMask::remove(unsigned int layer) 
{
	this->layers ^= layer;
}

bool LayerMask::contains(unsigned int layer) 
{
	return (this->layers & layer) == layer;
}