#include "gammacorrection.h"
#include "graphic.h"

using namespace spring;
using namespace spring::FX;

GammaCorrection::GammaCorrection() 
{
	this->gamma = 0.45f;
	this->fxType = "GammaCorrection";
}

void GammaCorrection::Initialize() 
{
	this->material = new Material(Shader::Load("fullscreen/fullscreen.vs", "postprocessing/gammacorrection.fs"));
}

void GammaCorrection::Release() 
{

}

void GammaCorrection::Process(FrameBuffer& srouce, FrameBuffer& destination) 
{
	this->material->SetFloat("gamma",this->gamma);
	Graphic::Blit(srouce, destination, *this->material);
}