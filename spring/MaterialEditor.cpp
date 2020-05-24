#include "materialeditor.h"
#include "selection.h"
#include "meshrenderer.h"
#include "shader.h"

using namespace spring;
using namespace spring::editor;

void MaterialEditor::OnDrawInspector() 
{
	MeshRenderer* meshRenderer = Selection::GetSelected()->GetNode<MeshRenderer>();
	if (nullptr == meshRenderer)
		return;
	Material* material = meshRenderer->material;
	if (nullptr == material)
		return;
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);

	if (ImGui::TreeNode("Material"))
	{
		ImGui::Checkbox("Enable Alpha Test", &material->alphaTest);
		ImGui::Checkbox("Enable Alpha Blend", &material->blend);

		ImGui::Checkbox("Enable Depth Test", &material->depthTest);
		ImGui::Checkbox("Enable Depth Write", &material->depthWrite);

		ImGui::Checkbox("Enable Stencil Test", &material->stencilTest);
		ImGui::Checkbox("Enable Cull Face", &material->cullface);

		ImGui::TreePop();
	}

	// lighting setting
	if (ImGui::TreeNode("Lighting"))
	{
		ImGui::Checkbox("Cast Shadow", &material->castShadow);;
		ImGui::Checkbox("Receive Shadow", &material->shader->receiveShadow);
		ImGui::TreePop();
	}

	// shader uniform properties
	if (ImGui::TreeNode("Shader Properties")) 
	{
		Shader* shader = material->shader;
		// map<GLuint, Colorf> colors;
		for (std::pair<const char*,ShaderColorfParams> pair : shader->_colors) 
		{ 
			Colorf color = pair.second.value;
			float* value = new float[4]{ color.r,color.g,color.b,color.a };
			ImGui::ColorEdit4(pair.first, value);
			shader->setColor(pair.first, Colorf(value[0], value[1], value[2], value[3]));
			delete[] value;
		}
		// map<GLuint, GLuint> ints;
		for (auto pair : shader->_ints)
		{ 
			int* value = new int[1]{(int)pair.second.value};
			ImGui::InputInt(pair.first, value);
			shader->setInt(pair.first, value[0]);
			delete[] value;
		}

		// map<GLuint, GLfloat> floats;
		for (auto pair : shader->_floats) 
		{
			float* value = new float[1] {pair.second.value};
			ImGui::InputFloat(pair.first, value);
			shader->setFloat(pair.first, value[0]);
			delete[] value;
		}

		// map<GLuint, Vector2> vec2Map;
		for (auto v2 : shader->_vec2s) 
		{
			float* value = new float[2]{ v2.second.value.x,v2.second.value.y };
			ImGui::DragFloat2(v2.first, value);
			shader->setVec2(v2.first, Vector2(value[0],value[1]));
			delete[] value;
		}
		// map<GLuint, Vector3> vec3Map;
		for (auto v3 : shader->_vec3s) 
		{
			float* value = new float[3]{v3.second.value.x,v3.second.value.y,v3.second.value.z};
			ImGui::InputFloat3(v3.first, value);
			shader->setVec3(v3.first, Vector3(value[0], value[1], value[2]));
			delete[] value;
		}
		// map<GLuint, Vector4> vec4Map;
		for (auto v4 : shader->_vec4s)
		{
			float* value = new float[4]{ v4.second.value.x,v4.second.value.y,v4.second.value.z ,v4.second.value.w};
			ImGui::InputFloat3(v4.first, value);
			shader->setVec4(v4.first, Vector4(value[0], value[1], value[2], value[3]));
			delete[] value;
		}
		// map<GLuint, glm::mat4> mat4Map;
		// map<GLuint, MaterialTexture> textures;
		for (auto tex : shader->_textures) 
		{
			ImGui::LabelText(tex.first,"");
			ImGui::ImageButton((ImTextureID)tex.second.value.texture, ImVec2(32, 32), ImVec2(0, 1), ImVec2(1, 0));
		}
		// map<GLuint, Cubemap*> cubemaps;
		for (auto cubemap : shader->_cubemaps)
		{
			ImGui::LabelText(cubemap.first, "");
			ImGui::ImageButton((ImTextureID)cubemap.second.value.cubemap, ImVec2(32, 32), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::TreePop();
	}
}