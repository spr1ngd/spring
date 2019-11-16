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

Mesh* GenerateCharacterMesh(Character* character)
{
	float halfWidth = character->size.x / 2.0f;
	float halfHeight = character->size.y / 2.0f;

	Mesh* mesh = new Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// left top
	Vertex lefttop;
	lefttop.vertex = Vector2(-halfWidth,halfHeight);
	lefttop.texcoord = Vector2(0.0f,1.0f);
	vertices.push_back(lefttop);

	// left bottom
	Vertex leftbottom;
	leftbottom.vertex = Vector2(-halfWidth,-halfHeight);
	leftbottom.texcoord = Vector2(0.0f,0.0f);
	vertices.push_back(leftbottom);

	// right bottom
	Vertex rightbottom;
	rightbottom.vertex = Vector2(halfWidth, -halfHeight);
	rightbottom.texcoord = Vector2(1.0f,0.0f);
	vertices.push_back(rightbottom);

	// right top
	Vertex rightop;
	rightop.vertex = Vector2(halfWidth,halfHeight);
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

	vector<Mesh> meshes;
	auto chars = this->text.c_str();
	int cLen = strlen(chars);
	for (int i = 0; i < cLen; i++)
	{
		char c = chars[i];
		Character* charcter = this->font->GetCharacter(c);
		Mesh* mesh = GenerateCharacterMesh(charcter);
		meshes.push_back(*mesh);
	}
	this->meshes = meshes;
	this->Init();
}

void Text::Render() 
{
	UIElement::Render();
}