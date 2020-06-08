#include "lighteditor.h"
#include "light.h"

using namespace spring::editor;

void LightEditor::OnDrawInspector() 
{
	Light* light = Selection::GetSelected()->GetNode<Light>();

	float intensity = light->setting.intensity;
	ImGui::DragFloat("Intensity", &intensity,1.0f,0.0f,100.0f,"%.1f");
	float* value = new float[4]{ light->color.r,light->color.g,light->color.b,light->color.a};
	ImGui::ColorEdit4("Color", value);
	Colorf color = Colorf(value[0],value[1],value[2],value[3]);
	light->SetLightParams(intensity, color);


	float smMapSize = light->shadowMapping.shadowMapSize;
	float smSize = light->shadowMapping.size;
	float smZNear = light->shadowMapping.zNear;
	float smZFar = light->shadowMapping.zFar;
	ImGui::DragFloat("size", &smSize);
	ImGui::DragFloat("zNear", &smZNear);
	ImGui::DragFloat("zFar", &smZFar);
	light->SetShadowMappingParams(smMapSize,smSize,smZNear,smZFar);

	if (nullptr != light->shadow)
	{
		ImGui::Text("ShadowMap");
		ImGui::SameLine();
		ImGui::Image((ImTextureID)light->shadow->GetBuffer(), ImVec2(256, 256), ImVec2(0, 1), ImVec2(1, 0));

		/*ImGui::Text("ShadowMap Blur");
		ImGui::SameLine();
		ImGui::Image((ImTextureID)light->tbuffer->GetBuffer(), ImVec2(256, 256), ImVec2(0, 1), ImVec2(1, 0));*/
	}
}