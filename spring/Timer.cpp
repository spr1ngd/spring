#include "timer.h"

using namespace spring;

float Timer::lastFrameTime = 0.0f;
float Timer::deltaTime = 0.0f;
float Timer::totalTime = 0.0f;

void Timer::Start()
{
	Timer::lastFrameTime = GetTickCount() * 0.001f;
	Timer::deltaTime = 0.0f;
}