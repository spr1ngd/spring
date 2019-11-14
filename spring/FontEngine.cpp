#include <freetype/ft2build.h>
#include FT_FREETYPE_H  
#include "fontengine.h"
#include "console.h"

using namespace std;
using namespace spring;

FontEngine::FontEngine() 
{

}

void FontEngine::LoadFont(const char* fontName) 
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		Console::ErrorFormat("[spring engine] Font engine could not init freetype library.");

	char* fontAsset = new char[] {"res/font/"};
	strcat(fontAsset, fontName);

	FT_Face face;
	if (FT_New_Face(ft, fontAsset, 0, &face))
		Console::ErrorFormat("[spring engine] Font engine load font fail.");

	FT_Set_Pixel_Sizes(face,0,48);

	char character = 's';
	if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		Console::ErrorFormat("[spring engine] Font engine load character %s fail.",character);

	Console::Log("load success.");
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}