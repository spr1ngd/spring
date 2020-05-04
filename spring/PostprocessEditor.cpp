#include "postprocesseditor.h"
#include "postprocessing.h"
#include "picking.h"

using namespace spring;
using namespace spring::editor;

void PostprocessEditor::OnDrawInspector() 
{
	class::PostProcessing* pp = PostProcessing::postprocessing;

	// picking framebuffer
	if (Picking::enable) 
	{
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);
		if (ImGui::CollapsingHeader("Picking"))
		{
			ImGui::Checkbox("Enable Picking", &Picking::enable);
			ImGui::Image((ImTextureID)Picking::pickBuffer->GetBuffer(), ImVec2(160.0f, 90.0f), ImVec2(0, 1), ImVec2(1, 0));
		}
	}

	if (pp->enabled == false)
		return;

	ImVec2 stdSize = ImVec2(160.0f,90.0f);

	// bloom setting
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::CollapsingHeader("Bloom")) 
	{
		ImGui::Checkbox("Enable Bloom", &pp->bloom->enable);

		float* color = new float[4]{pp->bloom->color.r,pp->bloom->color.g ,pp->bloom->color.b ,pp->bloom->color.a};
		ImGui::ColorEdit4("bloom color", color);
		pp->bloom->color = Colorf(color[0], color[1], color[2], color[3]);
		delete[] color;

		float* threshold = new float[1]{pp->bloom->threshold};
		ImGui::DragFloat("Threshold", threshold,0.01f,1.0f,5.0f);
		pp->bloom->threshold = threshold[0];
		delete[] threshold;
		if (pp->bloom->enable)
		{
			ImGui::Text("buffer 0");
			ImGui::Image((ImTextureID)pp->bloom->buffer->GetBuffer(1), stdSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Text("buffer 1");
			ImGui::Image((ImTextureID)pp->bloom->bloomTemp->GetBuffer(), stdSize, ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Text("bloom buffer");
			ImGui::Image((ImTextureID)pp->bloom->bloomBuffer->GetBuffer(), stdSize, ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::Separator();
	}

	// tone mapping
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::CollapsingHeader("ToneMapping")) 
	{
		ImGui::Checkbox("Enable ToneMapping",&pp->toneMapping->enable);
		float* exposure = new float[1]{pp->toneMapping->exposure};
		ImGui::DragFloat("exposure",exposure,0.1f,0.01f,5.0f);
		pp->toneMapping->exposure = exposure[0];
		if (pp->toneMapping->enable)
			ImGui::Image((ImTextureID)pp->toneMapping->buffer->GetBuffer(), stdSize, ImVec2(0, 1), ImVec2(1, 0));
		delete[] exposure;
		ImGui::Separator();
	}

	// outline
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::CollapsingHeader("Outline")) 
	{
		ImGui::Checkbox("Enable Outline",&pp->outline->enable);

		ImGui::Image((ImTextureID)pp->outline->buffer->GetBuffer(), stdSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)pp->outline->originBuffer->GetBuffer(), stdSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::Image((ImTextureID)pp->outline->blendBuffer->GetBuffer(), stdSize, ImVec2(0, 1), ImVec2(1, 0));

		float* color = new float[4]{ pp->outline->outlineColor.a,pp->outline->outlineColor.g,pp->outline->outlineColor.b,pp->outline->outlineColor.a };
		ImGui::ColorEdit4("outline Color", color);
		pp->outline->outlineColor = Colorf(color[0], color[1], color[2], color[3]);
		delete[] color;

		ImGui::DragInt("outline Width", &pp->outline->outlineWidth,1,0,10);
	}

	// anti-aliasing
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::CollapsingHeader("Anti-Aliasing")) 
	{
		bool enable = false;
		ImGui::Checkbox("Enable Anti-Aliasing",&enable);
		ImGui::Separator();
	}
}