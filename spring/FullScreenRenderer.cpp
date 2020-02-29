#include "fullscreenrenderer.h"
#include <vector>
#include "primitive.h"

using namespace std;
using namespace spring;

FullScreenRenderer::FullScreenRenderer() 
{
	
}

void FullScreenRenderer::Init() 
{
	this->layer = Layer::PostProcessing;
	this->material = new Material("res/shader/fullscreen/fullscreen.vs","res/shader/fullscreen/fullscreen.fs");

	vector<Mesh> meshes;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	
	Vertex lefttop;
	lefttop.vertex = Vector3(-1.0f, 1.0f, 0.0f);
	lefttop.texcoord = Vector2(0.0f, 1.0f);
	vertices.push_back(lefttop);
	
	Vertex leftbottom;
	leftbottom.vertex = Vector3(-1.0f, -1.0f, 0.0f);
	leftbottom.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(leftbottom);
	
	Vertex rightbottom;
	rightbottom.vertex = Vector3(1.0f, -1.0f, 0.0f);
	rightbottom.texcoord = Vector2(1.0f, 0.0f);
	vertices.push_back(rightbottom);
	
	Vertex righttop;
	righttop.vertex = Vector3(1.0f, 1.0f, 0.0f);
	righttop.texcoord = Vector2(1.0f, 1.0f);
	vertices.push_back(righttop);
	
	indices = { 0,1,2,2,3,0 };
	
	Mesh* mesh = new Mesh();
	mesh->vertices = vertices;
	mesh->indices = indices;
	meshes.push_back(*mesh);
	delete mesh;

	this->meshes = meshes;
	MeshRenderer::Init();
}