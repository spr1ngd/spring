#include <vector>
#include "primitive.h"
#include "console.h"
#include "meshrenderer.h"
#include "scene.h"

using namespace std;
using namespace spring;

#pragma region Create basic primitive gameobject

GameObject& Primitive::CreatePrimitive(Primitive::Type primitiveType) 
{
	switch (primitiveType) 
	{
	case Primitive::Triangle:
		return CreateTriangle();
	case Primitive::Plane:
		return CreatePlane();
	case Primitive::Cube:
		return CreateCube();
	case Primitive::Cylinder:
		return CreateCylinder();
	case Primitive::Sphere:
		return CreateSphere();
	default:
		PRINT_ERROR("[Primitive]:does not support to create %d",primitiveType);
		GameObject* primitive = new GameObject("Primitive");
		return *primitive;
		break;
	}
}

GameObject& Primitive::CreateTriangle() 
{
	GameObject* triangle = new GameObject("Triangle");
	return *triangle;
}

GameObject& Primitive::CreatePlane() 
{
	GameObject* plane = new GameObject("Plane");
	Mesh* planeMesh = GenPlane();
	MeshRenderer renderer = plane->AddNode<MeshRenderer>();
	renderer.material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer.mesh = planeMesh;
	renderer.Initialize();
	Scene::current->AddNode(plane);
	return *plane;
}

GameObject& Primitive::CreateCube() 
{
	GameObject* cube = new GameObject("Cube");
	return *cube;
}

GameObject& Primitive::CreateCylinder() 
{
	GameObject* cylinder = new GameObject("Cylinder");
	return *cylinder;
}

GameObject& Primitive::CreateSphere() 
{
	GameObject* sphere = new GameObject("Sphere");
	return *sphere;
}

#pragma endregion

#pragma region gen basic mesh 

Mesh* Primitive::GenPrimitive(Primitive::Type type)
{ 
	if (type == Primitive::Triangle) 
		return Primitive::GenTriangle();
	else if (type == Primitive::Plane) 
		return Primitive::GenPlane();
	else if (type == Primitive::Cube) 
		return Primitive::GenCube();
	else if (type == Primitive::Cylinder) 
		return Primitive::GenCylinder();
	else if (type == Primitive::Sphere) 
		return Primitive::GenSphere();
	else
	{
		PRINT_ERROR("[springengine::Primitive] : does not support to generate type [%d] primitive.", type);
		return nullptr;
	}
}

Mesh* Primitive::GenTriangle() 
{
	return nullptr;
}

Mesh* Primitive::GenPlane() 
{
	Mesh* mesh = new Mesh();
	mesh->mode = Mesh::Triangles;
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	Vertex lefttop;
	lefttop.vertex = Vector3(-.5f, .5f, 0.0f);
	lefttop.texcoord = Vector2(0.0f, 1.0f);
	vertices.push_back(lefttop);

	Vertex leftbottom;
	leftbottom.vertex = Vector3(-.5f, -.5f, 0.0f);
	leftbottom.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(leftbottom);

	Vertex rightbottom;
	rightbottom.vertex = Vector3(.5f, -.5f, 0.0f);
	rightbottom.texcoord = Vector2(1.0f, 0.0f);
	vertices.push_back(rightbottom);

	Vertex righttop;
	righttop.vertex = Vector3(.5f, .5f, 0.0f);
	righttop.texcoord = Vector2(1.0f, 1.0f);
	vertices.push_back(righttop);

	// indices
	indices = {0,1,2,2,3,0};
	mesh->vertices = vertices;
	mesh->indices = indices;
	return mesh;
}

Mesh* Primitive::GenCube() 
{
	return nullptr;
}

Mesh* Primitive::GenCylinder()
{
	return nullptr;
}

Mesh* Primitive::GenSphere() 
{
	return nullptr;
}

#pragma endregion