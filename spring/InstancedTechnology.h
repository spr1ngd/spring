#pragma once
#include "springengine.h"
#include "behaviour.h"

class InstancedTechnology : public spring::Behaviour
{
public:
	bool enabled = true;

	InstancedTechnology();
	void Awake() override;
	void Update() override;
	void Destroy() override;
};