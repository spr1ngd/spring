#include "behaviour.h"
#include "console.h"

using namespace spring; 

unsigned long Behaviour::count = 0;
std::map<const unsigned long, Behaviour*> Behaviour::behaviours;

Behaviour::Behaviour() 
{
	Behaviour::behaviours.insert(std::pair<const unsigned long, Behaviour*>(GetInstanceID(),this));
}

Behaviour::~Behaviour() 
{

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

void Behaviour::OnGUI() 
{

}

void Behaviour::OnPreRender() 
{

}

void Behaviour::OnPostRender()
{

}