#pragma once
#include "springengine.h"


using namespace spring;
using namespace spring::editor;

class Sample : public Behaviour
{
public:
	Sample();
	void Awake() override;
	void Update() override;
	void Destroy() override;
};