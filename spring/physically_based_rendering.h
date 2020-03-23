#pragma once
#include "springengine.h"

using namespace spring;
using namespace spring::editor;

class physically_based_rendering : public spring::Behaviour
{
public:
	physically_based_rendering();
	void Awake() override;
	void Update() override;
	void Destroy() override;
};