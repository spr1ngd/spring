#pragma once

namespace spring 
{
	class ShaderCompiler
	{
		// 自定义shader后缀文件
		// 加载特定后缀shader文件编译为Shader对象
		// 对指定目录下的文件进行监听，如果有新增、删除、变化都触发该shader文件的重新编译
		// 编辑指定后缀文件时，实现#inlcude方案
	private:
		// load and compile all shaders in this folder.
		void CompileShader(const char* folder);

	public:
		ShaderCompiler();
	};
}