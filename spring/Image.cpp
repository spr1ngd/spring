#include <vector>
#include "image.h"

using namespace spring;
using namespace spring::ui;

Image::Image() 
{
	
}

void Image::GenerateMesh() 
{
	Mesh* mesh = new Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	float halfWidth = this->rect->width / 2.0f;
	float halfHeight = this->rect->height / 2.0f;

	Vertex lefttop;
	lefttop.vertex = Vector3(-halfWidth, halfHeight,0.0f);
	lefttop.texcoord = Vector2(0.0f,1.0f);
	vertices.push_back(lefttop);

	Vertex leftbottom;
	leftbottom.vertex = Vector3(-halfWidth, -halfHeight, 0.0f);
	leftbottom.texcoord = Vector2(0.0f,0.0f);
	vertices.push_back(leftbottom);

	Vertex righttop;
	righttop.vertex = Vector3(halfWidth,halfHeight,0.0f);
	righttop.texcoord = Vector2(1.0f,1.0f);
	vertices.push_back(righttop);

	Vertex rightbottom;
	rightbottom.vertex = Vector3(halfWidth,-halfHeight,0.0f);
	rightbottom.texcoord = Vector2(1.0f,0.0f);
	vertices.push_back(rightbottom);

	indices = { 0,1,2,2,3,0 };

	mesh->vertices = vertices;
	mesh->indices = indices;
	this->meshes.push_back(*mesh);
}

void Image::Render() 
{

}