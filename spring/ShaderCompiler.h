#pragma once

namespace spring 
{
	class ShaderCompiler
	{
		// �Զ���shader��׺�ļ�
		// �����ض���׺shader�ļ�����ΪShader����
		// ��ָ��Ŀ¼�µ��ļ����м����������������ɾ�����仯��������shader�ļ������±���
		// �༭ָ����׺�ļ�ʱ��ʵ��#inlcude����
	private:
		// load and compile all shaders in this folder.
		void CompileShader(const char* folder);

	public:
		ShaderCompiler();
	};
}