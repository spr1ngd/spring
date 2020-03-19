#include "imgui.h"
#include "scenewindow.h"
#include "springengine.h"
#include "postprocessing.h"
#include "springeditor.h"

using namespace spring;
using namespace spring::editor;

SceneWindow::SceneWindow(const char* name, bool defaultOpen) :EditorWindow(name, defaultOpen)
{
	this->windowFlags = ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
}

void SceneWindow::BeginWindow() 
{
	float sceneWindowWidth = SpringEditor::maximize ? Screen::width : Screen::width * 0.6f + 30.0f;
	float sceneWInowHeight = SpringEditor::maximize ? Screen::height : Screen::height * 0.6f + 30.0f;
	if (SpringEditor::maximize)
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	else
		ImGui::SetNextWindowPos(ImVec2(0.0f, 50.0f));
	ImGui::SetNextWindowSize(ImVec2(sceneWindowWidth, sceneWInowHeight));
	ImGui::Begin(this->name, &this->enabled, this->windowFlags);
}

void SceneWindow::OnDrawWindow() 
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	float sceneWindowWidth = SpringEditor::maximize ? Screen::width : Screen::width * 0.6f;
	float sceneWInowHeight = SpringEditor::maximize ? Screen::height : Screen::height * 0.6f;
	unsigned int buffer = -1;

	if (nullptr != PostProcessing::postprocessing && PostProcessing::postprocessing->enabled)
		buffer = PostProcessing::outputFramebuffer->GetBuffer();
	else buffer = Camera::main->renderTarget->GetBuffer();

	ImGui::Image((ImTextureID)buffer, ImVec2(sceneWindowWidth, sceneWInowHeight), ImVec2(0, 1), ImVec2(1, 0),ImVec4(1.0f,1.0f,1.0f,1.0f),ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
}