#include "axishelper.h"
#include "meshrenderer.h"

using namespace spring;

AxisHelper::AxisHelper(Transform* trans)
{
	this->transform = trans;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	// x axis
	Vertex xStart;
	xStart.vertex = transform->position;
	xStart.color = Colorf::red;
	Vertex xEnd;
	xEnd.vertex = transform->position + transform->getRight();
	xEnd.color = Colorf::red;
	vertices.push_back(xStart);
	vertices.push_back(xEnd);
	indices.push_back(0);
	indices.push_back(1);

	// y axis
	Vertex yStart;
	yStart.vertex = transform->position;
	yStart.color = Colorf::green;
	Vertex yEnd;
	yEnd.vertex = transform->position + transform->getUp();
	yEnd.color = Colorf::green;
	vertices.push_back(yStart);
	vertices.push_back(yEnd);
	indices.push_back(2);
	indices.push_back(3);

	// z axis
	Vertex zStart;
	zStart.vertex = transform->position;
	zStart.color = Colorf::blue;
	Vertex zEnd;
	zEnd.vertex = transform->position + transform->getForword();
	zEnd.color = Colorf::blue;
	vertices.push_back(zStart);
	vertices.push_back(zEnd);
	indices.push_back(4);
	indices.push_back(5);

	Mesh mesh;
	mesh.vertices = vertices;
	mesh.indices = indices;
	mesh.mode = Mesh::Lines;
	vector<Mesh> meshes;
	meshes.push_back(mesh);

	this->mesh = &mesh;

	this->material = new Material("res/shader/vertex/vertexcolor.vs", "res/shader/vertex/vertexcolor.fs");
	this->material->name = "axis_color";
	this->material->renderMode = Material::Fill;	
	this->meshRenderer = new MeshRenderer(this->material);
	this->meshRenderer->meshes = meshes;
	this->meshRenderer->Init();
	this->meshRenderer->material->alphaTest = false;
	this->meshRenderer->material->depthTest = false;
	this->meshRenderer->setRenderOrder(5000);
}

void AxisHelper::RenderAxis() 
{
		
}

void AxisHelper::RenderRotator() 
{

}

void AxisHelper::RenderScaler() 
{

}

void AxisHelper::Render() 
{
	if (nullptr == this->transform)
		return;
	if (nullptr == this->meshRenderer)
		return;
	this->meshRenderer->transform->eulerangle = this->transform->eulerangle;
	switch (this->mode) 
	{
	case AxisHelper::Mode::Axis:
		this->RenderAxis();
		break;
	case AxisHelper::Mode::Rotate:
		this->RenderRotator();
		break;
	case AxisHelper::Mode::Scale:
		this->RenderScaler();
		break;
	default:
		break;
	}
}