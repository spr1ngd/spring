#include "axishelper.h"

using namespace spring;

void AxisHelper::RenderAxis() 
{
	// generate mesh
	this->mesh = new Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	// x axis
	Vertex xStart;
	xStart.vertex = Vector3::zero;
	xStart.color = Color::red;
	Vertex xEnd;
	xEnd.vertex = Vector3(1.0,0.0f,0.0f);
	xEnd.color = Color::red;
	vertices.push_back(xStart);
	vertices.push_back(xEnd);
	indices.push_back(0);
	indices.push_back(1);

	// y axis
	Vertex yStart;
	yStart.vertex = Vector3::zero;
	yStart.color = Color::green;
	Vertex yEnd;
	yEnd.vertex = Vector3(0.0f,1.0f,0.0f);
	yEnd.color = Color::green;
	vertices.push_back(yStart);
	vertices.push_back(yEnd);
	indices.push_back(2);
	indices.push_back(3);

	// z axis
	Vertex zStart;
	zStart.vertex = Vector3::zero;
	zStart.color = Color::blue;
	Vertex zEnd;
	zEnd.vertex = Vector3(0.0f,0.0f,-1.0f);
	zEnd.color = Color::blue;
	vertices.push_back(zStart);
	vertices.push_back(zEnd);
	indices.push_back(4);
	indices.push_back(5);

	this->mesh->vertices = vertices;
	this->mesh->indices = indices;
}

void AxisHelper::RenderRotator() 
{

}

void AxisHelper::RenderScaler() 
{

}

void AxisHelper::Render() 
{
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