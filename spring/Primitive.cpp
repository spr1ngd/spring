#include <vector>
#include "primitive.h"
#include "console.h"

using namespace std;
using namespace spring;

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