#include "particlerenderereditor.h"
#include "particlerenderer.h"
#include "selection.h"

using namespace spring;
using namespace spring::editor;

void ParticleRendererEditor::OnDrawInspector() 
{
	ParticleRenderer* particleRenderer = Selection::GetSelected()->GetNode<ParticleRenderer>();
	if (nullptr == particleRenderer)
		return;
	ImGui::SetNextItemOpen(true,ImGuiCond_Once);
	ImGui::Text(" %s","Basic Setting");

	ImGui::Checkbox("Is Playing",&particleRenderer->playing);
	int particleMaximum = (int)particleRenderer->maxNumber;
	ImGui::DragInt("Particle Maximum",&particleMaximum);
	particleRenderer->maxNumber = particleMaximum;

	int existingParticleNumber = (int)particleRenderer->existingNumber;
	ImGui::DragInt("Existing Maximum", &existingParticleNumber);
	particleRenderer->existingNumber = existingParticleNumber;

	float lifeTime = particleRenderer->lifeTime;
	ImGui::DragFloat("Life Time", &lifeTime);
	particleRenderer->lifeTime = lifeTime;

	ImGui::Text(" %s","Particle Shape");
	ImGui::Text(" %s","Parameters Setting");

	ImGui::Checkbox("Variable Color",&particleRenderer->enableVariableColor);
	float* beginColor = new float[4]
	{
		particleRenderer->beginColor.r,
		particleRenderer->beginColor.g,
		particleRenderer->beginColor.b,
		particleRenderer->beginColor.a
	};
	ImGui::ColorEdit4("Begin Color",beginColor,ImGuiColorEditFlags_DisplayRGB);
	particleRenderer->beginColor = Colorf
	(
		beginColor[0],
		beginColor[1],
		beginColor[2],
		beginColor[3]
	);
	delete[] beginColor;
	float* endColor = new float[4]
	{
		particleRenderer->endColor.r,
		particleRenderer->endColor.g,
		particleRenderer->endColor.b,
		particleRenderer->endColor.a
	};
	ImGui::ColorEdit4("End Color", endColor, ImGuiColorEditFlags_DisplayRGB);
	particleRenderer->endColor = Colorf
	(
		endColor[0],
		endColor[1],
		endColor[2],
		endColor[3]
	);
	delete[] endColor;
	ImGui::Checkbox("Variable Velocity",&particleRenderer->enableVariableVelocity);
	ImGui::DragFloat("Start Velocity", &particleRenderer->beginVelocity);
	ImGui::DragFloat("End Velocity", &particleRenderer->endVelocity);

	ImGui::Checkbox("Variable Size", &particleRenderer->enableVariableSize);
	ImGui::DragFloat("Start Size", &particleRenderer->beginSize);
	ImGui::DragFloat("End Size", &particleRenderer->endSize);

	ImGui::Checkbox("Variable Emit Speed", &particleRenderer->enableVariableEmitSpeed);
	ImGui::DragFloat("Start Emit Speed", &particleRenderer->beginSpeed);
	ImGui::DragFloat("End Emit Speed", &particleRenderer->endSpeed);
}