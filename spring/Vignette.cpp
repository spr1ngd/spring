#include "vignette.h"
#include "graphic.h"
#include "shaderproperty.h"

using namespace spring;
using namespace spring::FX;

Vignette::Vignette() : color(Colorf::white),center(Vector2::zero),intensity(0.5f),smoothness(1.0f),roundness(0.5f),rounded(false)
{
	this->rounded = true;
	this->fxType = "Vignette";
}

void Vignette::Initialize() 
{
	this->material = new Material(Shader::Load("fullscreen/fullscreen.vs", "postprocessing/vignette/vignette.fs"));
}

void Vignette::Release() 
{

}

void Vignette::Process(FrameBuffer& source, FrameBuffer& destination) 
{
	if (this->vignetteType == VignetteType::Classical) 
	{
		this->material->SetFloat("_Mode",0.0f);
		this->material->SetColor(ShaderProperty::_MaskTex, this->color);
		this->material->SetVec2("_Center", this->center);
		this->material->SetFloat("_Intensity", this->intensity);
		this->material->SetFloat("_Smoothness", this->smoothness);
		//this->material->SetFloat("_Roundness", this->roundness);
		//this->material->SetBool("_Rounded", this->rounded);
	}
	else if (this->vignetteType == VignetteType::Mask) 
	{
		this->material->SetFloat("_Mode", 1.0f);
		if (nullptr != this->maskTex) this->material->SetTexture(ShaderProperty::_MaskTex, this->maskTex);
		else  this->material->SetTexture(ShaderProperty::_MaskTex, TextureLoader::CreatePureBlackTexture());
	}
	Graphic::Blit(source, destination, *this->material);
}