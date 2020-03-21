#include "springengine.h"
#include "axishelper.h"
#include "meshrenderer.h"
#include "gizmos.h"

using namespace spring;

AxisHelper::AxisHelper(Vector3 target) 
{
	this->space = CoordinateSpace::World;
	this->target = nullptr;

	this->material = new Material(Shader::Load("vertex/vertexcolor.vs", "vertex/vertexcolor.fs"));
	this->material->name = "axis_color";
	this->material->renderMode = Material::Fill;
	this->meshRenderer = new MeshRenderer(this->material);
	this->RenderAxis();
	this->meshRenderer->setRenderOrder(5000);
}

AxisHelper::AxisHelper(Transform* trans, CoordinateSpace space)
{
	this->space = space;
	this->target = trans;

	this->material = new Material(Shader::Load("vertex/vertexcolor.vs", "vertex/vertexcolor.fs"));
	this->material->name = "axis_color";
	this->material->renderMode = Material::Fill;	
	this->meshRenderer = new MeshRenderer(this->material);
	this->RenderAxis();
	this->meshRenderer->setRenderOrder(5000);
}

void AxisHelper::Render() 
{
	if (nullptr == this->meshRenderer)
		return;
	if (nullptr != this->target)
	{
		this->meshRenderer->transform->SetPosition(this->target->GetPosition());
		this->meshRenderer->transform->SetEulerangle(Vector3::zero);
	}
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

void AxisHelper::RenderAxis() 
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	// x axis
	Vertex xStart;
	xStart.vertex = Vector3::zero;
	Vertex xEnd;

	if (this->space == CoordinateSpace::Self && this->target != nullptr)
	{
		xEnd.vertex = this->target->right;
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
	if (this->space == CoordinateSpace::Self && this->target != nullptr)
	{
		yEnd.vertex = this->target->up;
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
	if (this->space == CoordinateSpace::Self && this->target != nullptr)
	{
		zEnd.vertex = this->target->forword;
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
	// vector<Mesh> meshes;
	//meshes.push_back(mesh);

	this->mesh = &mesh;
	// this->meshRenderer->meshes = meshes;
	this->meshRenderer->mesh = &mesh;
	this->meshRenderer->Init();
}

void AxisHelper::RenderRotator()
{

}

void AxisHelper::RenderScaler()
{

}