#include "gizmos.h"
#include "transform.h"
#include "matrix4x4.h"
#include "console.h"

using namespace std;
using namespace spring;
 
bool Gizmos::enable = false;
vector<AxisHelper*> Gizmos::axisHelpers;
vector<Gizmos*> Gizmos::gizmos;
CoordinateSpace Gizmos::space = CoordinateSpace::World;
Colorf Gizmos::color = Colorf::gray;

void Gizmos::DrawAxis(Vector3 pos , Vector3 size)
{
	AxisHelper* axis = new AxisHelper(pos);
	axis->meshRenderer->transform->SetScale(size);
	axisHelpers.push_back(axis);
}

void Gizmos::DrawAxis(Transform* transform,Vector3 size)
{
	AxisHelper* axis = new AxisHelper(transform);
	axis->meshRenderer->transform->SetScale(size);
	axisHelpers.push_back(axis);
}

void Gizmos::DrawLine(Vector3 origin, Vector3 end) 
{
	Gizmos* gizmos = new Gizmos();
	// material
	gizmos->material = new Material(Shader::Load("vertex/vertexcolor.vs", "vertex/vertexcolor.fs"));
	gizmos->material->name = "gizmos";
	gizmos->material->renderMode = Material::Fill;
	// mesh renderer
	gizmos->meshrenderer = new MeshRenderer(gizmos->material);
	gizmos->meshrenderer->setRenderOrder(5000);

	// meshes
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Vertex startPoint;
	startPoint.vertex = origin;
	startPoint.color = Gizmos::color;
	Vertex endPoint;
	endPoint.vertex = end;
	endPoint.color = Gizmos::color;
	vertices.push_back(startPoint);
	vertices.push_back(endPoint);
	indices.push_back(0);
	indices.push_back(1);

	gizmos->mesh = new Mesh();
	gizmos->mesh->vertices = vertices;
	gizmos->mesh->indices = indices;
	gizmos->mesh->mode = Mesh::Lines;
	vector<Mesh> meshes;
	meshes.push_back(*gizmos->mesh);

	gizmos->meshrenderer->meshes = meshes;
	gizmos->meshrenderer->Init();
	Gizmos::gizmos.push_back(gizmos);
} 

void Gizmos::DrawCircle(Vector3 pos, Vector3 up, float radius, unsigned int smoothness)
{
	Gizmos* gizmos = new Gizmos();
	// material 
	Material* material = new Material(Shader::Load("vertex/vertexcolor.vs", "vertex/vertexcolor.fs"));
	material->name = "circle material";
	material->renderMode = Material::RenderMode::Fill;
	gizmos->material = material;

	// meshrenderer
	gizmos->meshrenderer = new MeshRenderer(gizmos->material);
	gizmos->meshrenderer->setRenderOrder(5000);

	// meshes
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Vector3 rotateAxis = Vector3::Normalize(up);
	Vector3 helper = Vector3::Normalize(Vector3::Cross(rotateAxis, Vector3::right)); 

	Gizmos::color = Colorf::megenta;
	float perAngle = 360.0f / Mathf::Clamp(smoothness, 12, 120);
	Matrix4x4 T = Matrix4x4::Translate(-pos.x, -pos.y, -pos.z);
	Matrix4x4 IT = Matrix4x4::Translate(pos.x, pos.y, pos.z);

	for (unsigned int i = 0; i < smoothness; i++)
	{
		Vertex vertex;
		Vector3 base = helper;
		float angle = perAngle * i;
		Matrix4x4 R = Matrix4x4::Rotate(angle, up);
		base = IT * R * T * base;
		vertex.vertex = pos + base * radius;
		vertex.color = Gizmos::color;
		vertices.push_back(vertex);
		indices.push_back(i);
	}

	Mesh mesh;
	mesh.vertices = vertices;
	mesh.indices = indices;
	mesh.mode = Mesh::LineLoop;
	vector<Mesh> meshes;
	meshes.push_back(mesh);

	gizmos->meshrenderer->meshes = meshes;
	gizmos->meshrenderer->Init();
	Gizmos::gizmos.push_back(gizmos);
} 

void Gizmos::Render() 
{
	if (enable == false)
		return;
	for (auto pair : axisHelpers) 
		pair->Render();
}