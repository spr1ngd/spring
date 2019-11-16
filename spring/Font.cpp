#include "font.h"
#include "fontengine.h"

using namespace std;
using namespace spring;

Font::Font(const char* fontName)
{
	this->name = fontName;
	FontEngine::LoadFont(*this);
}

void Font::AddCharacter(Character* character) 
{
	std::map<char,Character*>::iterator item = this->characters.find(character->c);
	if (item != this->characters.end())
		return;
	this->characters[character->c] = character;
}

Character* Font::GetCharacter(char c)
{
	auto item = this->characters.find(c);
	if (item == this->characters.end())
		return nullptr;
	return item->second;
}