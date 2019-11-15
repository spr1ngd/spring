#include <ft2build.h>
#include FT_FREETYPE_H  
#include "fontengine.h"
#include "console.h"
#include "glew.h"
#include "vector2.h"

#pragma comment(lib,"freetype.lib")

using namespace std;
using namespace spring;

FontEngine::FontEngine() 
{

}

Character* LoadCharacter(FT_Face& face, char c)
{
	if (FT_Load_Char(face, c, FT_LOAD_RENDER))
	{
		Console::ErrorFormat("[spring engine] Font engine load character %s fail.", c);
		return nullptr;
	}

	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	Character* character = new Character();
	character->c = c;
	character->size = Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
	character->bearing = Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top);
	character->advance = face->glyph->advance.x;
	character->character = textureId;
	return character;
}

void FontEngine::LoadFont(Font& font)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		Console::ErrorFormat("[spring engine] Font engine could not init freetype library.");

	char fontAsset[] = {"res/font/"};

	// todo : 
	// strcat(fontAsset, fontName);
	strcat_s(fontAsset, font.name);

	FT_Face face;
	if (FT_New_Face(ft, fontAsset, 0, &face))
		Console::ErrorFormat("[spring engine] Font engine load font %s fail.",font.name);

	FT_Set_Pixel_Sizes(face,0,48);

	for (char c = 0; c < 127; c++)
	{
		auto character = LoadCharacter(face, c);
		if( nullptr == character )
			continue;
		font.AddCharacter(character);
	}

	Console::LogFormat("[spring engine] Font engine load font %s successfully.",font.name);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}