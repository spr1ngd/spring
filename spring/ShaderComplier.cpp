#include "shadercompiler.h"
#include <iostream>
#include <thread>
#include "console.h"

using namespace std;
using namespace spring;
thread::id main_thread_id = this_thread::get_id();

ShaderCompiler::ShaderCompiler()
{
	thread shader_compiler_thread(this->ObserveShaderFiles);
	shader_compiler_thread.join();
}

void ShaderCompiler::ObserveShaderFiles()
{
	// 只去读取程序中已经加载的shader文件
	Console::Log("i am other thread.please look at me.");
}