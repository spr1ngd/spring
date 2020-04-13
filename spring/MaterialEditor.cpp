#include "materialeditor.h"
#include "selection.h"
#include "meshrenderer.h"

using namespace spring;
using namespace spring::editor;

void MaterialEditor::OnDrawInspector() 
{
	MeshRenderer* meshRenderer = Selection::gameobject->GetNode<MeshRenderer>();
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
		for (auto color : shader->colors) 
		{
			const char* name = shader->getUniformName(color.first);
			float* value = new float[4]{ color.second.r,color.second.g,color.second.b,color.second.a };
			ImGui::ColorEdit4(name, value);
			shader->setColor(name, Colorf(value[0], value[1], value[2], value[3]));
			delete[] value;
		}
		// map<GLuint, GLuint> ints;
		for (auto pair : shader->ints)
		{
			const char* name = shader->getUniformName(pair.first);
			int* value = new int[1]{(int)pair.second};
			ImGui::InputInt(name, value);
			shader->setInt(name, value[0]);
			delete[] value;
		}

		// map<GLuint, GLfloat> floats;
		for (auto pair : shader->floats) 
		{
			const char* name = shader->getUniformName(pair.first);
			float* value = new float[1] {pair.second};
			ImGui::InputFloat(name, value);
			shader->setFloat(name, value[0]);
			delete[] value;
		}

		// map<GLuint, Vector2> vec2Map;
		for (auto v2 : shader->vec2Map) 
		{
			const char* name = shader->getUniformName(v2.first);
			float* value = new float[2]{ v2.second.x,v2.second.y };
			ImGui::DragFloat2(name, value);
			shader->setVec2(name, Vector2(value[0],value[1]));
			delete[] value;
		}
		// map<GLuint, Vector3> vec3Map;
		for (auto v3 : shader->vec3Map) 
		{
			const char* name = shader->getUniformName(v3.first);
			float* value = new float[3]{v3.second.x,v3.second.y,v3.second.z};
			ImGui::InputFloat3(name, value);
			shader->setVec3(name, Vector3(value[0], value[1], value[2]));
			delete[] value;
		}
		// map<GLuint, Vector4> vec4Map;
		for (auto v4 : shader->vec4Map)
		{
			const char* name = shader->getUniformName(v4.first);
			float* value = new float[4]{ v4.second.x,v4.second.y,v4.second.z ,v4.second.w};
			ImGui::InputFloat3(name, value);
			shader->setVec4(name, Vector4(value[0], value[1], value[2], value[3]));
			delete[] value;
		}
		// map<GLuint, glm::mat4> mat4Map;
		// map<GLuint, MaterialTexture> textures;
		for (auto tex : shader->textures) 
		{
			const char* name = shader->getUniformName(tex.first);
			ImGui::LabelText(name,"");
			ImGui::ImageButton((ImTextureID)tex.second.texture, ImVec2(32, 32), ImVec2(0, 1), ImVec2(1, 0));
		}
		// map<GLuint, Cubemap*> cubemaps;
		for (auto cubemap : shader->cubemaps)
		{
			const char* name = shader->getUniformName(cubemap.first);
			ImGui::LabelText(name, "");
			ImGui::ImageButton((ImTextureID)cubemap.second->cubemap, ImVec2(32, 32), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::TreePop();
	}
}