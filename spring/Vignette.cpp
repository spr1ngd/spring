#include "vignette.h"
#include "graphic.h"

using namespace spring;
using namespace spring::FX;

Vignette::Vignette() : color(Colorf::white),center(Vector2::half),intensity(0.5f),smoothness(1.0f),roundness(0.5f),rounded(false)
{

}

void Vignette::Initialize() 
{
	this->fxType = "Vignette";

	this->material = new Material(Shader::Load("fullscreen/fullscreen.vs", "postprocessing/vignette/vignette.fs"));
	this->material->SetColor(_MainColor,this->color);
	this->material->SetVec2("_Center",this->center);
	this->material->SetFloat("_Intensity", this->intensity);
	this->material->SetFloat("_Smoothness",this->smoothness);
	this->material->SetFloat("_Roundness", this->roundness);
	this->material->SetBool("_Rounded",this->rounded);
	if (nullptr != this->maskTex)
		this->material->SetTexture(_MaskTex, this->maskTex);
}

void Vignette::Release() 
{

}

void Vignette::Process(FrameBuffer& source, FrameBuffer& destination) 
{
	Graphic::Blit(source, destination, *this->material);
}