
#pragma once

#include "springengine.h"

using namespace spring;

// scene entrance
class GameApp : public Behaviour
{
public:
	void Awake() override;
	void Update() override;
	void Destroy() override;
};