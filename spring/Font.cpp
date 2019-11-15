#include "font.h"
#include "fontengine.h"

using namespace std;
using namespace spring;

Font::Font(char* fontName)
{
	this->name = fontName;
	FontEngine::LoadFont(*this);
}

void Font::AddCharacter(Character* character) 
{

}

void Font::GetCharacter(char c) 
{

}