#include "materialeditor.h"
#include "selection.h"
#include "meshrenderer.h"

using namespace spring;
using namespace spring::editor;

MaterialEditor::MaterialEditor(const char* windowName, bool defaultOpen) : InspectorEditor(windowName, defaultOpen)
{
	
}

void MaterialEditor::OnDrawInspector() 
{
	if (Selection::node == nullptr)
		return;

	MeshRenderer* meshRenderer = (MeshRenderer*)Selection::node;
	if (nullptr == meshRenderer)
		return;

	ImGui::SetNextItemOpen(true, ImGuiCond_Once);

	// material name
	// get material properties
	// draw properties
	Material* material = meshRenderer->material;
	if (nullptr == material)
		return;
	
	// funcs
	if (ImGui::TreeNode("Material"))
	{
		ImGui::Text("Name(%s)",meshRenderer->name);

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
		ImGui::Checkbox("Receive Shadow", &material->receiveShadow);
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
			// color.second = Colorf(value[0], value[1], value[2],value[3]);
			delete[] value;
		}
		// map<GLuint, GLuint> ints;
		
		// map<GLuint, GLfloat> floats;
		// map<GLuint, Vector2> vec2Map;
		for (auto v2 : shader->vec2Map) 
		{
			const char* name = shader->getUniformName(v2.first);
			float* value = new float[2]{ v2.second.x,v2.second.y };
			ImGui::DragFloat2(name, value);
			// v2.second = Vector2(value[0],value[1]);
			delete[] value;
		}
		// map<GLuint, Vector3> vec3Map;
		// map<GLuint, Vector4> vec4Map;
		// map<GLuint, glm::mat4> mat4Map;
		// map<GLuint, MaterialTexture> textures;
		// map<GLuint, Cubemap*> cubemaps;
		ImGui::TreePop();
	}
}