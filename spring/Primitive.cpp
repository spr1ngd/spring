#include <vector>
#include "primitive.h"
#include "console.h"

using namespace std;
using namespace spring;

Mesh* Primitive::GenPrimitive(Primitive::Type type)
{ 
	if (type == Primitive::Triangle) 
		return this->GenTriangle();
	else if (type == Primitive::Plane) 
		return this->GenPlane();
	else if (type == Primitive::Cube) 
		return this->GenCube();
	else if (type == Primitive::Cylinder) 
		return this->GenCylinder();
	else if (type == Primitive::Sphere) 
		return this->GenSphere();
	else
	{
		Console::ErrorFormat("[springengine::Primitive] : does not support to generate type [%d] primitive.", type);
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

	// first
	Vertex first;
	first.vertex = Vector3(-1.0f,1.0f,0.0f);
	vertices.push_back(first);
	// second
	Vertex second;
	second.vertex = Vector3(-1.0f,-1.0f,0.0f);
	vertices.push_back(second);
	// third
	Vertex third;
	third.vertex = Vector3(1.0f,-1.0f,0.0f);
	vertices.push_back(third);
	// fourth
	Vertex fourth;
	fourth.vertex = Vector3(1.0f,1.0f,0.0f);
	vertices.push_back(fourth);

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