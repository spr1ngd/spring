#include <vector>
#include "image.h"
#include "console.h"

using namespace spring;
using namespace spring::ui;

Image::Image()
{
	this->texture = nullptr;
}

void Image::GenerateMesh()
{ 
	if (nullptr == this->material)
	{
		Material* uiMaterial = new Material("res/shader/ui/default.vs","res/shader/ui/default.fs");
		this->material = uiMaterial;
	}
	this->setRenderOrder(10000);

	vector<Vertex> vertices;
	vector<unsigned int> indices;

	float halfWidth = this->rect->width / 2.0f;
	float halfHeight = this->rect->height / 2.0f;

	halfWidth = 0.5f;
	halfHeight = 0.5f;

	Vertex lefttop;
	lefttop.vertex = Vector3(-halfWidth, halfHeight, 0.0f);
	lefttop.texcoord = Vector2(0.0f, 1.0f);
	lefttop.color = Colorf::red;
	vertices.push_back(lefttop);

	Vertex leftbottom;
	leftbottom.vertex = Vector3(-halfWidth, -halfHeight, 0.0f);
	leftbottom.texcoord = Vector2(0.0f, 0.0f);
	leftbottom.color = Colorf::green;
	vertices.push_back(leftbottom);

	Vertex rightbottom;
	rightbottom.vertex = Vector3(halfWidth, -halfHeight, 0.0f);
	rightbottom.texcoord = Vector2(1.0f, 0.0f);
	rightbottom.color = Colorf::blue;
	vertices.push_back(rightbottom);

	Vertex righttop;
	righttop.vertex = Vector3(halfWidth, halfHeight, 0.0f);
	righttop.texcoord = Vector2(1.0f, 1.0f);
	righttop.color = Colorf::white;
	vertices.push_back(righttop);

	indices = { 0,1,2,2,3,0 };

	Mesh* mesh = new Mesh();
	mesh->vertices = vertices;
	mesh->indices = indices;
	 
	this->meshes.push_back(*mesh);
	this->Init();
}

void Image::Render()
{
	if (nullptr != this->texture)
		this->material->shader->setTexture(MAIN_TEX,this->texture->textureId);
	UIElement::Render();
}