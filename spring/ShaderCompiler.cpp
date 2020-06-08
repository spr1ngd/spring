#include "shadercompiler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "console.h"

using namespace std;
using namespace spring;
thread::id main_thread_id = this_thread::get_id();

ShaderCompiler::ShaderCompiler()
{

}