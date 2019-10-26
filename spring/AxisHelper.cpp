#include "springengine.h"
#include "axishelper.h"
#include "meshrenderer.h"
#include "gizmos.h"

using namespace spring;

AxisHelper::AxisHelper(Transform* trans)
{
	this->target = trans;

	this->material = new Material("res/shader/vertex/vertexcolor.vs", "res/shader/vertex/vertexcolor.fs");
	this->material->name = "axis_color";
	this->material->renderMode = Material::Fill;	
	this->meshRenderer = new MeshRenderer(*this->material);
	this->SetGizmosMode(Gizmos::GetMode());
	this->meshRenderer->material.alphaTest = false;
	this->meshRenderer->material.depthTest = false;
	this->meshRenderer->setRenderOrder(5000);
}

void AxisHelper::RenderAxis() 
{
	this->SetGizmosMode(Gizmos::GetMode());
}

void AxisHelper::RenderRotator() 
{

}

void AxisHelper::RenderScaler() 
{

}

void AxisHelper::Render() 
{
	if (nullptr == this->target)
		return;
	if (nullptr == this->meshRenderer)
		return;
	this->meshRenderer->transform->SetPosition(this->target->GetPosition());
	auto euler = this->target->GetEulerangle();
	Console::LogFormat("%f,%f,%f",euler.x,euler.y,euler.z);
	this->meshRenderer->transform->SetEulerangle(this->target->GetEulerangle());
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

void AxisHelper::SetGizmosMode(unsigned int mode) 
{ 
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	// x axis
	Vertex xStart;
	xStart.vertex = Vector3::zero;
	Vertex xEnd;
	
	if (mode == Space::Self) 
	{
		// todo : direction of rotation is different
		xEnd.vertex = this->meshRenderer->transform->right;
	}
	else
	{
		xEnd.vertex = Vector3::right;
	}
	xStart.color = Colorf::red;
	xEnd.color = Colorf::red;
	vertices.push_back(xStart);
	vertices.push_back(xEnd);
	indices.push_back(0);
	indices.push_back(1);

	// y axis
	Vertex yStart;
	yStart.vertex = Vector3::zero;
	Vertex yEnd;
	if (mode == Space::Self)
	{
		yEnd.vertex = this->meshRenderer->transform->up;
	}
	else 
	{
		yEnd.vertex = Vector3::up;
	}
	yStart.color = Colorf::green;
	yEnd.color = Colorf::green;
	vertices.push_back(yStart);
	vertices.push_back(yEnd);
	indices.push_back(2);
	indices.push_back(3);

	// z axis
	Vertex zStart;
	zStart.vertex = Vector3::zero;
	Vertex zEnd;
	if (mode == Space::Self)
	{
		zEnd.vertex = this->meshRenderer->transform->forword;
	}
	else 
	{
		zEnd.vertex = Vector3::forward;
	}
	zStart.color = Colorf::blue;
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
	this->meshRenderer->meshes = meshes;
	this->meshRenderer->Init();
}