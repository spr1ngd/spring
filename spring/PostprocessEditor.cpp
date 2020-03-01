#include "postprocesseditor.h"
#include "postprocessing.h"

using namespace spring;
using namespace spring::editor;

PostprocessEditor::PostprocessEditor(const char*name,bool openDefault) : InspectorEditor(name,openDefault)
{
	
}

void PostprocessEditor::OnDrawInspector() 
{
	class::PostProcessing* pp = PostProcessing::postprocessing;
	if (pp->enabled == false)
		return;

	// bloom setting
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::CollapsingHeader("Bloom")) 
	{
		ImGui::Checkbox("Enable Bloom", &pp->bloom->enable);
		if (pp->bloom->enable)
		{
			ImGui::Text("buffer 0");
			ImGui::Image((ImTextureID)pp->bloom->buffer->buffers[0], ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Text("buffer 1");
			ImGui::Image((ImTextureID)pp->bloom->buffer->buffers[1], ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0));
			ImGui::Text("bloom buffer");
			ImGui::Image((ImTextureID)pp->bloom->bloomBuffer->buffer, ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0));
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
			ImGui::Image((ImTextureID)pp->toneMapping->buffer->buffer, ImVec2(64, 64), ImVec2(0, 1), ImVec2(1, 0));
		delete[] exposure;
		ImGui::Separator();
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