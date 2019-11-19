#include "text.h"
#include "console.h"
#include <vector>

using namespace spring;
using namespace spring::ui;

Text::Text()
{

}

void Text::SetText(string text) 
{
	// todo : call the generate mesh
	this->text = text;
	if (text.empty())
		return;
	this->GenerateMesh();
}

string Text::GetText() 
{
	return this->text;
}

Mesh* GenerateCharacterMesh(Character* character , Vector2 origin )
{ 
	Vector2 offset = origin + Vector2(character->bearing.x ,character->bearing.y - character->size.y);

	Mesh* mesh = new Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// left top
	Vertex lefttop;
	lefttop.vertex = Vector2(0.0f,character->size.y) + offset;
	lefttop.texcoord = Vector2(0.0f,1.0f);
	vertices.push_back(lefttop);

	// left bottom
	Vertex leftbottom;
	leftbottom.vertex = Vector2(0.0f,0.0f) + offset;
	leftbottom.texcoord = Vector2(0.0f,0.0f);
	vertices.push_back(leftbottom);

	// right bottom
	Vertex rightbottom;
	rightbottom.vertex = Vector2(character->size.x,0.0f) + offset;
	rightbottom.texcoord = Vector2(1.0f,0.0f);
	vertices.push_back(rightbottom);

	// right top
	Vertex rightop;
	rightop.vertex = Vector2(character->size.x,character->size.y) + offset;
	rightop.texcoord = Vector2(1.0f,1.0f);
	vertices.push_back(rightop);

	// indices
	indices = {0,1,2,2,3,0};

	// textures
	textures.push_back(*character->character);

	mesh->vertices = vertices;
	mesh->indices = indices;
	mesh->textures = textures;
	return mesh;
}

void Text::GenerateMesh() 
{
	if (nullptr == this->font)
	{
		Console::ErrorFormat("[spring engine] : text does not have font.");
		return;
	}
	if (nullptr == this->material)
		this->material = new Material("res/shader/ui/default.vs", "res/shader/ui/default.fs");
	this->setRenderOrder(10000);

	std::vector<Mesh>().swap(this->meshes);
	Vector2 origin = Vector2(-this->rectTransform->size.x / 2.0f,0.0f);
	vector<Mesh> meshes;

	if (this->richText == false)
	{
		auto chars = this->text.c_str();
		int cLen = strlen(chars);
		for (int i = 0; i < cLen; i++)
		{
			Character* character = this->font->GetCharacter(chars[i]);
			Mesh* mesh = GenerateCharacterMesh(character, origin);
			origin += Vector2((float)character->advance + this->characterSpace, 0.0f);
			meshes.push_back(*mesh);
			delete mesh;
		}
	}
	else  // support rich text
	{
		vector<RichText*> richTexts;
		auto chars = this->text.c_str();
		int cLen = strlen(chars);
		for (int i = 0; i < cLen; i++)
		{
			Character* character = this->font->GetCharacter(chars[i]);
			RichText* richText = new RichText();
			richText->character = character;
			richTexts.push_back(richText);
		}

		string leftBracket = "<";
		string rightBracket = ">";
		string slash = "/";

		vector<string> tags;
		// get tags index
		for (auto tag : this->htmlTags) 
		{
			string beginTag = leftBracket + tag + rightBracket;
			string endTag = leftBracket + slash + tag + rightBracket;
			tags.push_back(beginTag);
			tags.push_back(endTag);
		}

		for (auto tag : tags) 
		{
			Console::ErrorFormat("search %s",tag.c_str());

			int index = 0;
			while ((index = this->text.find(tag.c_str(), index)) != string::npos)
			{
				Console::LogFormat("find %s in %d", tag.c_str(), index);
				index = index + tag.length();
			}
		}

		for (int i = 0; i < cLen; i++)
		{
			Character* character = this->font->GetCharacter(chars[i]);
			Mesh* mesh = GenerateCharacterMesh(character, origin);
			origin += Vector2((float)character->advance + this->characterSpace, 0.0f);
			meshes.push_back(*mesh);
			delete mesh;
		}
	}
	this->meshes = meshes;
	this->Init();
}

string* Text::parseTags(string text)
{
	return nullptr;
}

void Text::Render() 
{
	UIElement::Render();
}