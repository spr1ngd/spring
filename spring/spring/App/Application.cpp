#include "Application.h"
#include <iostream>
#include "console.h"

using namespace std;
using namespace spring;

void Application::Initialize()
{
	Console::Log("spring engine start up...");
}

void Application::Render()
{
	Console::Log("application render.");
}