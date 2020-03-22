#pragma once

#include "springengine.h"

using namespace spring;

class springengine_scene : public Behaviour
{
public:
	void Awake() override;
	void Update() override;
};

