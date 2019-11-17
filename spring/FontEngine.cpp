#include <ft2build.h>
#include FT_FREETYPE_H  
#include "fontengine.h"
#include "console.h"
#include "glew.h"
#include "vector2.h"

#pragma comment(lib,"freetype.lib")

using namespace std;
using namespace spring;

std::map<const char*, Font*> FontEngine::fonts;

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
	unsigned int width = face->glyph->bitmap.width;
	unsigned int height = face->glyph->bitmap.rows;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	Character* character = new Character();
	character->c = c;
	character->size = Vector2((float)width, (float)height);
	character->bearing = Vector2((float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top);
	character->advance = face->glyph->advance.x / 64;
	auto texture = new Texture();
	texture->textureId = textureId;
	character->character = texture;
	return character;
}

void FontEngine::LoadFont(Font& font)
{
	// load cached asset
	auto cache = fonts.find(font.name);
	if (cache != fonts.end()) 
	{
		font = *cache->second;
		return;
	}

	// create new font asset
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		Console::ErrorFormat("[spring engine] Font engine could not init freetype library.");

	char src[] = { "res/font/\0" };
	auto srcLen = strlen(src);
	auto nameLen = strlen(font.name);
	char* fontAsset = new char[srcLen + nameLen + 1]{};
	memcpy(fontAsset, src, srcLen);
	memcpy(fontAsset + srcLen, font.name, nameLen);
	FT_Face face;
	if (FT_New_Face(ft, fontAsset, 0, &face))
		Console::ErrorFormat("[spring engine] Font engine load font %s fail.", font.name);
	delete[] fontAsset;

	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (byte c = 0; c < 128; c++)
	{
		auto character = LoadCharacter(face, c);
		if (nullptr == character)
		{
			Console::ErrorFormat("[spring engine] : Font engine load character %s failed.",c);
			continue;
		}
		font.AddCharacter(character);
	}

	Console::LogFormat("[spring engine] Font engine load font %s successfully.", font.name);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	// cache font asset
	fonts[font.name] = &font;
}