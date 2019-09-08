#include "FPS.h"

using namespace spring;
using namespace spring::editor;

float FPS::lastFrameTime = 0.0f;// timeGetTime() * 0.001f;
int FPS::fps = 0;