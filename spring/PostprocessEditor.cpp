#include "postprocesseditor.h"
#include "postprocessing.h"
#include "picking.h"

using namespace spring;
using namespace spring::editor;

void ColorField(const char* fieldName,Colorf& value) 
{
	float* color = new float[4]{ value.r,value.g ,value.b ,value.a };
	ImGui::ColorEdit4(fieldName, color);
	value = Colorf(color[0], color[1], color[2], color[3]);
	delete[] color;
}

void Vec2Field( const char* fieldName, Vector2& value ) 
{
	float* vec2 = new float[2]{ value.x,value.y };
	ImGui::InputFloat2(fieldName, vec2);
	value.x = vec2[0];
	value.y = vec2[1];
}

void DragFloatField(const char* fieldName, float& value, float min = 0.0f, float max = 1.0f, float speed = 0.01f)
{
	ImGui::DragFloat(fieldName, &value, speed, min, max);
}

void CheckField( const char* fieldName, bool& value )
{
	ImGui::Checkbox(fieldName, &value);
}

void TextureField(const char* fieldName, Texture* texture, Vector2 size = Vector2(256, 256), Vector2 uv0 = Vector2(0, 1), Vector2 uv1 = Vector2(1, 0))
{
	ImGui::Text(fieldName);

	if (nullptr == texture)
	{
		if (ImGui::Button("upload")) 
		{
			PRINT_LOG("upload texture.");
		}
	}
	else
	{
		if (ImGui::ImageButton((ImTextureID)(texture->textureId), ImVec2(size.x, size.y), ImVec2(uv0.x, uv0.y), ImVec2(uv1.x, uv1.y))) 
		{
			PRINT_LOG("replace texture");
		}
	}
}

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

	// vignette
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::CollapsingHeader("Vignette"))
	{
		Vignette* vignette = pp->GetFX<Vignette>();
		bool vignetteEnabled = nullptr != vignette && vignette->enable;
		ImGui::Checkbox("Enable Vignette", &vignetteEnabled);
		vignette = pp->SetFX<Vignette>(vignetteEnabled);
		if (vignetteEnabled)
		{ 
			ColorField("color", vignette->color);
			Vec2Field("center", vignette->center);
			DragFloatField("intensity", vignette->intensity);
			DragFloatField("smoothness",vignette->smoothness);
			DragFloatField("roundness",vignette->roundness);
			CheckField("rounded",vignette->rounded);
			TextureField("mask texture",vignette->maskTex);
		}
	}

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