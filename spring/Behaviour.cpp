#include "Behaviour.h"

using namespace spring; 

unsigned long Behaviour::count = 0;
std::map<const unsigned long, Behaviour*> Behaviour::behaviours;

Behaviour::Behaviour() 
{
	Behaviour::behaviours.insert(std::pair<const unsigned long, Behaviour*>(GetInstanceID(),this));
}

void Behaviour::Awake()
{

}

void Behaviour::Update() 
{

}

void Behaviour::Destroy() 
{

}