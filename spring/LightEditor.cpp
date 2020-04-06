#include "lighteditor.h"
#include "light.h"

using namespace spring::editor;

void LightEditor::OnDrawInspector() 
{
	Light* light = Selection::gameobject->GetNode<Light>();

	ImGui::DragFloat("Intensity",&light->intensity,1.0f,0.0f,100.0f,"%.1f");

	float* value = new float[4]{ light->color.r / 255.0f,light->color.g / 255.0f,light->color.b / 255.0f,light->color.a / 255.0f };
	ImGui::ColorEdit4("Color", value);
	light->color = Colorf(value[0],value[1],value[2],value[3]);

	if (nullptr != light->shadow)
	{
		ImGui::Text("ShadowMap");
		ImGui::SameLine();
		ImGui::Image((ImTextureID)light->shadow->GetBuffer(), ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::Text("ShadowMap T");
		ImGui::SameLine();
		ImGui::Image((ImTextureID)light->tbuffer->GetBuffer(), ImVec2(128, 128), ImVec2(0, 1), ImVec2(1, 0));
	}
}