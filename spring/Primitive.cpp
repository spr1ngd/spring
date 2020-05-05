#include <vector>
#include "primitive.h"
#include "console.h"
#include "meshrenderer.h"
#include "scene.h"
#include "modelloader.h"

using namespace std;
using namespace spring;

#pragma region Create basic primitive gameobject

GameObject* Primitive::CreateGizmo(Primitive::GizmoType gizmoType) 
{
	switch (gizmoType)
	{
	case spring::Primitive::Move:
		return CreateGizmoMove();
	case spring::Primitive::Rotate:
		return CreateGizmoRotate();
	case spring::Primitive::Scale:
		return CreateGizmoScale();
	default:
		PRINT_ERROR("[Primitive]:does not support to create %d", gizmoType);
		GameObject* gizmo = new GameObject("gizmo");
		return gizmo;
		break;
	}
}

GameObject* Primitive::CreatePrimitive(Primitive::Type primitiveType)
{
	switch (primitiveType)
	{
	case Primitive::Triangle:
		return CreateTriangle();
	case Primitive::Quad:
		return CreateQuad();
	case Primitive::Plane:
		return CreatePlane();
	case Primitive::Cube:
		return CreateCube();
	case Primitive::Cylinder:
		return CreateCylinder();
	case Primitive::Cone:
		return CreateCone();
	case Primitive::Sphere:
		return CreateSphere();
	case Primitive::Band:
		return CreateBand();
	case Primitive::Mobiusband:
		return CreateMobiusband();
	default:
		PRINT_ERROR("[Primitive]:does not support to create %d", primitiveType);
		GameObject* primitive = new GameObject("Primitive");
		return primitive;
		break;
	}
}

GameObject* Primitive::CreateTriangle()
{
	GameObject* triangle = new GameObject("Triangle");
	Mesh* tirangleMesh = GenTriangle();
	MeshRenderer* renderer = triangle->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->mesh = tirangleMesh;
	return triangle;
}

GameObject* Primitive::CreateQuad()
{
	auto plane = new GameObject("Quad");
	Mesh* quadMesh = GenQuad();
	auto renderer = plane->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = quadMesh;
	return plane;
}

GameObject* Primitive::CreatePlane() 
{
	auto plane = new GameObject("Plane");
	Mesh* planeMesh = GenPlane();
	auto renderer = plane->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = planeMesh;
	return plane;
}

GameObject* Primitive::CreateCube()
{
	GameObject* cube = new GameObject("Cube");
	Mesh* cubeMesh = GenCube();
	MeshRenderer* renderer = cube->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = cubeMesh;
	return cube;
}

GameObject* Primitive::CreateCylinder()
{
	GameObject* cylinder = new GameObject("Cylinder");
	Mesh* cylinderMesh = GenCylinder();
	MeshRenderer* renderer = cylinder->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs","diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = cylinderMesh;
	return cylinder;
}

GameObject* Primitive::CreateCone()
{
	GameObject* cone = new GameObject("Cone");
	Mesh* coneMesh = GenCone();
	MeshRenderer* renderer = cone->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = coneMesh;
	return cone;
}

GameObject* Primitive::CreateSphere()
{
	GameObject* sphere = new GameObject("Sphere");
	Mesh* sphereMesh = GenSphere();
	MeshRenderer* renderer = sphere->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = sphereMesh;
	return sphere;
}

GameObject* Primitive::CreateBand(float bRadius, float sRadius, unsigned int bSubdivision, unsigned int sSubdivision)
{
	GameObject* band = new GameObject("Band");
	Mesh* bandMesh = GenBand(bRadius, sRadius, bSubdivision, sSubdivision);
	MeshRenderer* renderer = band->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = bandMesh;
	return band;
}

GameObject* Primitive::CreateMobiusband() 
{
	GameObject* mobiusband = new GameObject("Mobiusband");
	Mesh* mobiusbandMesh = GenMobiusband();
	MeshRenderer* renderer = mobiusband->AddNode<MeshRenderer>();
	renderer->material = new Material(Shader::Load("diffuse/diffuse.vs", "diffuse/diffuse.fs"));
	renderer->material->shader->setColor(MAIN_COLOR, Color::gray);
	renderer->mesh = mobiusbandMesh;
	return mobiusband;
}

GameObject* Primitive::CreateGizmoMove()
{
	GameObject* moveGizmo = new GameObject("editor_gizmos_move");
	// moveGizmo->flags = HideFlags::HideFlags_HideInHierarchyWindow;

	// x axis
	Material* xAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	xAxisMaterial->shader->setColor(MAIN_COLOR, Color::red);
	xAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* xAxis = new GameObject("editor_gizmos_x");
	xAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* xAxisRenderer = xAxis->AddNode<MeshRenderer>();
	xAxisRenderer->material = xAxisMaterial;
	xAxisRenderer->setRenderOrder(15000);
	Mesh* xAxisMesh = GenPrimitive(Primitive::Type::Cylinder);
	Matrix4x4 xAxisRTS = Matrix4x4::RTS(Vector3(0.5f,0.0f,0.0f), Vector3(0.02f, 1.0f, 0.02f), Vector3(0.0f, 0.0f, -90.0f));
	xAxisMesh->RTS(xAxisRTS);
	Mesh* xAxisArrowMesh = GenPrimitive(Primitive::Type::Cone);
	Matrix4x4 xAxisArrowRTS = Matrix4x4::RTS(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.2f, 0.4f, 0.2f), Vector3(0.0f, 0.0f, -90.0f));
	xAxisArrowMesh->RTS(xAxisArrowRTS);
	xAxisMesh->Combine(*xAxisArrowMesh);
	delete xAxisArrowMesh;
	xAxisRenderer->mesh = xAxisMesh;
	xAxis->SetParent(moveGizmo);

	// y axis
	Material* yAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	yAxisMaterial->shader->setColor(MAIN_COLOR, Color::blue);
	yAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* yAxis = new GameObject("editor_gizmos_y");
	yAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* yAxisRenderer = yAxis->AddNode<MeshRenderer>();
	yAxisRenderer->setRenderOrder(15000);
	yAxisRenderer->material = yAxisMaterial;
	Mesh* yAxisMesh = GenPrimitive(Primitive::Type::Cylinder);
	Matrix4x4 yAxisRTS = Matrix4x4::RTS(Vector3(0.0f, 0.5f, 0.0f), Vector3(0.02f, 1.0f, 0.02f), Vector3(0.0f, 0.0f, 0.0f));
	yAxisMesh->RTS(yAxisRTS);	
	Mesh* yAxisArrowMesh = GenPrimitive(Primitive::Type::Cone);
	Matrix4x4 yAxisArrowRTS = Matrix4x4::RTS(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.2f, 0.4f, 0.2f), Vector3(0.0f, 0.0f, 0.0f));
	yAxisArrowMesh->RTS(yAxisArrowRTS);
	yAxisMesh->Combine(*yAxisArrowMesh);
	delete yAxisArrowMesh;
	yAxisRenderer->mesh = yAxisMesh;
	yAxis->SetParent(moveGizmo);

	// z axis
	Material* zAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	zAxisMaterial->shader->setColor(MAIN_COLOR, Color::green);
	zAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* zAxis = new GameObject("editor_gizmos_z");
	zAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* zAxisRenderer = zAxis->AddNode<MeshRenderer>();
	zAxisRenderer->setRenderOrder(15000);
	zAxisRenderer->material = zAxisMaterial;
	Mesh* zAxisMesh = GenPrimitive(Primitive::Type::Cylinder);
	Matrix4x4 zAxisRTS = Matrix4x4::RTS(Vector3(0.0f, 0.0f, 0.5f), Vector3(0.02f, 1.0f, 0.02f), Vector3(90.0f, 0.0f, 0.0f));
	zAxisMesh->RTS(zAxisRTS);
	Mesh* zAxisArrowMesh = GenPrimitive(Primitive::Type::Cone);
	Matrix4x4 zAxisArrowRTS = Matrix4x4::RTS(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.2f, 0.4f, 0.2f), Vector3(90.0f, 0.0f, 0.0f));
	zAxisArrowMesh->RTS(zAxisArrowRTS);
	zAxisMesh->Combine(*zAxisArrowMesh);
	delete zAxisArrowMesh;
	zAxisRenderer->mesh = zAxisMesh;
	zAxis->SetParent(moveGizmo);
	return moveGizmo;
}

GameObject* Primitive::CreateGizmoScale() 
{
	GameObject* scaleGizmo = new GameObject("editor_gizmos_scale");

	// x axis
	Material* xAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	xAxisMaterial->shader->setColor(MAIN_COLOR, Color::red);
	xAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* xAxis = new GameObject("editor_gizmos_x");
	xAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* xAxisRenderer = xAxis->AddNode<MeshRenderer>();
	xAxisRenderer->material = xAxisMaterial;
	xAxisRenderer->setRenderOrder(15000);
	Mesh* xAxisMesh = GenPrimitive(Primitive::Type::Cylinder);
	Matrix4x4 xAxisRTS = Matrix4x4::RTS(Vector3(0.5f, 0.0f, 0.0f), Vector3(0.02f, 1.0f, 0.02f), Vector3(0.0f, 0.0f, -90.0f));
	xAxisMesh->RTS(xAxisRTS);
	Mesh* xAxisArrowMesh = GenPrimitive(Primitive::Type::Cube);
	Matrix4x4 xAxisArrowRTS = Matrix4x4::RTS(Vector3(1.0f, 0.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0.0f, 0.0f, 0.0f));
	xAxisArrowMesh->RTS(xAxisArrowRTS);
	xAxisMesh->Combine(*xAxisArrowMesh);
	delete xAxisArrowMesh;
	xAxisRenderer->mesh = xAxisMesh;
	xAxis->SetParent(scaleGizmo);

	// y axis
	Material* yAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	yAxisMaterial->shader->setColor(MAIN_COLOR, Color::blue);
	yAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* yAxis = new GameObject("editor_gizmos_y");
	yAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* yAxisRenderer = yAxis->AddNode<MeshRenderer>();
	yAxisRenderer->setRenderOrder(15000);
	yAxisRenderer->material = yAxisMaterial;
	Mesh* yAxisMesh = GenPrimitive(Primitive::Type::Cylinder);
	Matrix4x4 yAxisRTS = Matrix4x4::RTS(Vector3(0.0f, 0.5f, 0.0f), Vector3(0.02f, 1.0f, 0.02f), Vector3(0.0f, 0.0f, 0.0f));
	yAxisMesh->RTS(yAxisRTS);
	Mesh* yAxisArrowMesh = GenPrimitive(Primitive::Type::Cube);
	Matrix4x4 yAxisArrowRTS = Matrix4x4::RTS(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0.0f, 0.0f, 0.0f));
	yAxisArrowMesh->RTS(yAxisArrowRTS);
	yAxisMesh->Combine(*yAxisArrowMesh);
	delete yAxisArrowMesh;
	yAxisRenderer->mesh = yAxisMesh;
	yAxis->SetParent(scaleGizmo);

	// z axis
	Material* zAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	zAxisMaterial->shader->setColor(MAIN_COLOR, Color::green);
	zAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* zAxis = new GameObject("editor_gizmos_z");
	zAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* zAxisRenderer = zAxis->AddNode<MeshRenderer>();
	zAxisRenderer->setRenderOrder(15000);
	zAxisRenderer->material = zAxisMaterial;
	Mesh* zAxisMesh = GenPrimitive(Primitive::Type::Cylinder);
	Matrix4x4 zAxisRTS = Matrix4x4::RTS(Vector3(0.0f, 0.0f, 0.5f), Vector3(0.02f, 1.0f, 0.02f), Vector3(90.0f, 0.0f, 0.0f));
	zAxisMesh->RTS(zAxisRTS);
	Mesh* zAxisArrowMesh = GenPrimitive(Primitive::Type::Cube);
	Matrix4x4 zAxisArrowRTS = Matrix4x4::RTS(Vector3(0.0f, 0.0f, 1.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0.0f, 0.0f, 0.0f));
	zAxisArrowMesh->RTS(zAxisArrowRTS);
	zAxisMesh->Combine(*zAxisArrowMesh);
	delete zAxisArrowMesh;
	zAxisRenderer->mesh = zAxisMesh;
	zAxis->SetParent(scaleGizmo);
	return scaleGizmo;
}

GameObject* Primitive::CreateGizmoRotate() 
{
	GameObject* rotateGizmo = new GameObject("editor_gizmos_rotate");

	// x axis
	Material* xAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	xAxisMaterial->shader->setColor(MAIN_COLOR, Color::red);
	xAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* xAxis = new GameObject("editor_gizmos_x");
	xAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* xAxisRenderer = xAxis->AddNode<MeshRenderer>();
	xAxisRenderer->material = xAxisMaterial;
	xAxisRenderer->setRenderOrder(15000);
	Mesh* xAxisMesh = GenBand(1.0f, 0.01f, 128, 16);
	xAxisMesh->RTS(Matrix4x4::RTS(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f,1.0f,1.0f), Vector3(0.0f, 0.0f, 90.0f)));
	xAxisRenderer->mesh = xAxisMesh;
	xAxis->SetParent(rotateGizmo);

	// y axis
	Material* yAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	yAxisMaterial->shader->setColor(MAIN_COLOR, Color::blue);
	yAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* yAxis = new GameObject("editor_gizmos_y");
	yAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* yAxisRenderer = yAxis->AddNode<MeshRenderer>();
	yAxisRenderer->setRenderOrder(15000);
	yAxisRenderer->material = yAxisMaterial;
	Mesh* yAxisMesh = GenBand(1.0f, 0.01f, 128, 16);
	// yAxisMesh->RTS(Matrix4x4::RTS(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 90.0f)));
	yAxisRenderer->mesh = yAxisMesh;
	yAxis->SetParent(rotateGizmo);

	// z axis
	Material* zAxisMaterial = new Material(Shader::Load("editor/gizmos/editor_gizmos_axis.vs", "editor/gizmos/editor_gizmos_axis.fs"));
	zAxisMaterial->shader->setColor(MAIN_COLOR, Color::green);
	zAxisMaterial->DepthTestFunc(true, GL_ALWAYS, true);
	GameObject* zAxis = new GameObject("editor_gizmos_z");
	zAxis->SetFlag(HideFlags_NotEditable);
	MeshRenderer* zAxisRenderer = zAxis->AddNode<MeshRenderer>();
	zAxisRenderer->setRenderOrder(15000);
	zAxisRenderer->material = zAxisMaterial;
	Mesh* zAxisMesh = GenBand(1.0f, 0.01f, 128, 16);
	zAxisMesh->RTS(Matrix4x4::RTS(Vector3(0.0f, 0.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f), Vector3(90.0f, 0.0f, 0.0f)));
	zAxisRenderer->mesh = zAxisMesh;
	zAxis->SetParent(rotateGizmo);

	return rotateGizmo;
}

#pragma endregion

#pragma region gen basic mesh 

Mesh* Primitive::GenPrimitive(Primitive::Type type)
{ 
	if (type == Primitive::Triangle)
		return Primitive::GenTriangle();
	else if (type == Primitive::Quad)
		return Primitive::GenQuad();
	else if (type == Primitive::Cube)
		return Primitive::GenCube();
	else if (type == Primitive::Cylinder)
		return Primitive::GenCylinder();
	else if (type == Primitive::Cone)
		return Primitive::GenCone();
	else if (type == Primitive::Sphere)
		return Primitive::GenSphere();
	else if (type == Primitive::Band)
		return Primitive::GenBand();
	else if (type == Primitive::Mobiusband)
		return Primitive::GenMobiusband();
	else
	{
		PRINT_ERROR("[springengine::Primitive] : does not support to generate type [%d] primitive.", type);
		return nullptr;
	}
}

Mesh* Primitive::GenTriangle() 
{
	Mesh* triangle = new Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vertex top;
	top.vertex = Vector3(0.0f, 0.57735026f, 0.0f);
	top.texcoord = Vector2(0.5f,1.0f);
	top.normal = Vector3(0.0f,0.0f,1.0f);
	vertices.push_back(top);

	Vertex left;
	left.vertex = Vector3(-0.5f,-0.288675134f,0.0f);
	left.texcoord = Vector2(0.0f,0.0f);
	left.normal = Vector3(0.0f, 0.0f, 1.0f);
	vertices.push_back(left);

	Vertex right;
	right.vertex = Vector3(0.5f, -0.288675134f, 0.0f);
	right.texcoord = Vector2(1.0f,0.0f);
	right.normal = Vector3(0.0f, 0.0f, 1.0f);
	vertices.push_back(right);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	 
	triangle->vertices = vertices;
	triangle->indices = indices;

	return triangle;
}

Mesh* Primitive::GenQuad() 
{
	Mesh* plane = new Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Vertex first;
	first.vertex = Vector3(0.5f,0.0f,0.5f);
	first.texcoord = Vector2(1.0f,0.0f);
	first.normal = Vector3(0.0f,1.0f,0.0f);
	vertices.push_back(first);

	Vertex second;
	second.vertex = Vector3(0.5f,0.0f,-0.5f);
	second.texcoord = Vector2(1.0f,1.0f);
	second.normal = Vector3(0.0f,1.0f,0.0f);
	vertices.push_back(second);

	Vertex third;
	third.vertex = Vector3(-0.5f,0.0f,-0.5f);
	third.texcoord = Vector2(0.0f,1.0f);
	third.normal = Vector3(0.0f,1.0f,0.0f);
	vertices.push_back(third);

	Vertex fourth;
	fourth.vertex = Vector3(-0.5f,0.0f,0.5f);
	fourth.texcoord = Vector2(0.0f,0.0f);
	fourth.normal = Vector3(0.0f,1.0f,0.0f);
	vertices.push_back(fourth);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);

	plane->vertices = vertices;
	plane->indices = indices;
	return plane;
}

Mesh* Primitive::GenPlane() 
{
	int subdivision = 512;
	float length = 10.0f;
	float perLength = length / subdivision;
	float perUV = 1.0 / subdivision;
	Vector3 origin = Vector3(length * 0.5f, 0.0f, length * 0.5f);
	Vector2 uvOrigin = Vector2(1.0f,0.0f);

	Mesh* plane = new Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int x = 0; x <= subdivision; x++) 
	{
		for (unsigned int z = 0; z <= subdivision; z++) 
		{
			Vertex vertex;
			vertex.vertex = origin + Vector3(-perLength * x, 0.0f,-perLength * z);
			vertex.normal = Vector3(0.0f,1.0f,0.0f);
			vertex.texcoord = uvOrigin + Vector2(-perUV * x, perUV * z);
			vertices.push_back(vertex);

			if (z < subdivision && x < subdivision) 
			{
				indices.push_back((subdivision + 1) * x + z);
				indices.push_back((subdivision + 1) * x + z + 1);
				indices.push_back((subdivision + 1) * x + z + 2 + subdivision);
				
				indices.push_back((subdivision + 1) * x + z + 2 + subdivision);
				indices.push_back((subdivision + 1) * x + z + 1 + subdivision);
				indices.push_back((subdivision + 1) * x + z);
			}
		}
	}

	plane->vertices = vertices;
	plane->indices = indices;

	return plane;
}

Mesh* Primitive::GenCube() 
{
	Mesh* cube = new Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int indicesCount = 0;
	// bottom
	Vertex b1; b1.vertex = Vector3(0.5f, -0.5f, 0.5f);  b1.normal = Vector3(0.0f, -1.0f, 0.0f); b1.texcoord = Vector2(1.0f, 1.0f);
	Vertex b2; b2.vertex = Vector3(0.5f, -0.5f, -0.5f); b2.normal = Vector3(0.0f, -1.0f, 0.0f); b2.texcoord = Vector2(1.0f, 0.0f);
	Vertex b3; b3.vertex = Vector3(-0.5f, -0.5f, -0.5f); b3.normal = Vector3(0.0f, -1.0f, 0.0f); b3.texcoord = Vector2(0.0f, 0.0f);
	Vertex b4; b4.vertex = Vector3(-0.5f, -0.5f, 0.5f); b4.normal = Vector3(0.0f, -1.0f, 0.0f); b4.texcoord = Vector2(0.0f, 1.0f);
	vertices.push_back(b2);
	vertices.push_back(b1);
	vertices.push_back(b4);
	vertices.push_back(b3);
	indices.push_back(indicesCount + 0); indices.push_back(indicesCount + 1); indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 2); indices.push_back(indicesCount + 3); indices.push_back(indicesCount + 0);

	// top
	indicesCount = vertices.size();
	Vertex t1; t1.vertex = Vector3(0.5f, 0.5f, 0.5f);	t1.normal = Vector3(0.0f, 1.0f, 0.0f);	t1.texcoord = Vector2(1.0f, 0.0f);
	Vertex t2; t2.vertex = Vector3(0.5f, 0.5f, -0.5f);	t2.normal = Vector3(0.0f, 1.0f, 0.0f);	t2.texcoord = Vector2(1.0f, 1.0f);
	Vertex t3; t3.vertex = Vector3(-0.5f, 0.5f, -0.5f);	t3.normal = Vector3(0.0f, 1.0f, 0.0f);	t3.texcoord = Vector2(0.0f, 1.0f);
	Vertex t4; t4.vertex = Vector3(-0.5f, 0.5f, 0.5f);	t4.normal = Vector3(0.0f, 1.0f, 0.0f);	t4.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(t1);
	vertices.push_back(t2);
	vertices.push_back(t3);
	vertices.push_back(t4);
	indices.push_back(indicesCount + 0); indices.push_back(indicesCount + 1); indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 2); indices.push_back(indicesCount + 3); indices.push_back(indicesCount + 0);

	// right
	indicesCount = vertices.size();
	Vertex r1; r1.vertex = Vector3(0.5f, -0.5f, -0.5f); r1.normal = Vector3(1.0f, 0.0f, 0.0f); r1.texcoord = Vector2(1.0f, 0.0f);
	Vertex r2; r2.vertex = Vector3(0.5f, 0.5f, -0.5f);  r2.normal = Vector3(1.0f, 0.0f, 0.0f); r2.texcoord = Vector2(1.0f, 1.0f);
	Vertex r3; r3.vertex = Vector3(0.5f, 0.5f, 0.5f);   r3.normal = Vector3(1.0f, 0.0f, 0.0f); r3.texcoord = Vector2(0.0f, 1.0f);
	Vertex r4; r4.vertex = Vector3(0.5f, -0.5f, 0.5f);  r4.normal = Vector3(1.0f, 0.0f, 0.0f); r4.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(r1);
	vertices.push_back(r2);
	vertices.push_back(r3);
	vertices.push_back(r4);
	indices.push_back(indicesCount + 0); indices.push_back(indicesCount + 1); indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 2); indices.push_back(indicesCount + 3); indices.push_back(indicesCount + 0);

	// left
	indicesCount = vertices.size();
	Vertex l1; l1.vertex = Vector3(-0.5f, -0.5f, 0.5f);  l1.normal = Vector3(-1.0f, 0.0f, 0.0f); l1.texcoord = Vector2(1.0f, 0.0f);
	Vertex l2; l2.vertex = Vector3(-0.5f, 0.5f, 0.5f);   l2.normal = Vector3(-1.0f, 0.0f, 0.0f); l2.texcoord = Vector2(1.0f, 1.0f);
	Vertex l3; l3.vertex = Vector3(-0.5f, 0.5f, -0.5f);  l3.normal = Vector3(-1.0f, 0.0f, 0.0f); l3.texcoord = Vector2(0.0f, 1.0f);
	Vertex l4; l4.vertex = Vector3(-0.5f, -0.5f, -0.5f); l4.normal = Vector3(-1.0f, 0.0f, 0.0f); l4.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(l1);
	vertices.push_back(l2);
	vertices.push_back(l3);
	vertices.push_back(l4);
	indices.push_back(indicesCount + 0); indices.push_back(indicesCount + 1); indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 2); indices.push_back(indicesCount + 3); indices.push_back(indicesCount + 0);

	// forward
	indicesCount = vertices.size();
	Vertex f1; f1.vertex = Vector3(0.5f, -0.5f, 0.5f);  f1.normal = Vector3(0.0f, 0.0f, 1.0f); f1.texcoord = Vector2(1.0f, 0.0f);
	Vertex f2; f2.vertex = Vector3(0.5f, 0.5f, 0.5f);   f2.normal = Vector3(0.0f, 0.0f, 1.0f); f2.texcoord = Vector2(1.0f, 1.0f);
	Vertex f3; f3.vertex = Vector3(-0.5f, 0.5f, 0.5f);  f3.normal = Vector3(0.0f, 0.0f, 1.0f); f3.texcoord = Vector2(0.0f, 1.0f);
	Vertex f4; f4.vertex = Vector3(-0.5f, -0.5f, 0.5f); f4.normal = Vector3(0.0f, 0.0f, 1.0f); f4.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(f1);
	vertices.push_back(f2);
	vertices.push_back(f3);
	vertices.push_back(f4);
	indices.push_back(indicesCount + 0); indices.push_back(indicesCount + 1); indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 2); indices.push_back(indicesCount + 3); indices.push_back(indicesCount + 0);

	// back
	indicesCount = vertices.size();
	Vertex back1; back1.vertex = Vector3(-0.5f, -0.5f, -0.5f);  back1.normal = Vector3(0.0f, 0.0f, -1.0f); back1.texcoord = Vector2(1.0f, 0.0f);
	Vertex back2; back2.vertex = Vector3(-0.5f, 0.5f, -0.5f);   back2.normal = Vector3(0.0f, 0.0f, -1.0f); back2.texcoord = Vector2(1.0f, 1.0f);
	Vertex back3; back3.vertex = Vector3(0.5f, 0.5f, -0.5f);    back3.normal = Vector3(0.0f, 0.0f, -1.0f); back3.texcoord = Vector2(0.0f, 1.0f);
	Vertex back4; back4.vertex = Vector3(0.5f, -0.5f, -0.5f);   back4.normal = Vector3(0.0f, 0.0f, -1.0f); back4.texcoord = Vector2(0.0f, 0.0f);
	vertices.push_back(back1);
	vertices.push_back(back2);
	vertices.push_back(back3);
	vertices.push_back(back4);
	indices.push_back(indicesCount + 0); indices.push_back(indicesCount + 1); indices.push_back(indicesCount + 2);
	indices.push_back(indicesCount + 2); indices.push_back(indicesCount + 3); indices.push_back(indicesCount + 0);

	cube->vertices = vertices;
	cube->indices = indices;
	return cube;
}

Mesh* Primitive::GenCylinder()
{
	float radius = 0.5f;
	float height = 1.0f;
	unsigned int subdivision = 64;

	Mesh* cylinder = new Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int vertexCount = 0;
	int centerIndex = vertices.size();
	// top
	Vector3 tc = Vector3(0.0f, height * 0.5f, 0.0f);
	Vertex top;
	top.vertex = tc;
	top.normal = Vector3(0.0f, 1.0f, 0.0f);
	vertices.push_back(top);
	vertexCount = vertices.size();
	for (unsigned int i = 0; i <= subdivision; i++)
	{
		Vertex vertex;
		float radian = (i * 1.0f / subdivision) * Mathf::pi * 2;
		float x = Mathf::Cos(radian);
		float z = Mathf::Sin(radian);
		vertex.vertex = tc + Vector3(x, 0.0f, z) * radius;
		vertex.normal = Vector3(0.0f, 1.0f, 0.0f);
		vertices.push_back(vertex);
		if (i < subdivision)
		{
			indices.push_back(vertexCount + i);
			indices.push_back(centerIndex);
			indices.push_back(vertexCount + i + 1);
		}
	}

	// bottom
	centerIndex = vertices.size();
	Vector3 bc = Vector3(0.0f, height * -0.5f,0.0f);
	Vertex bottom;
	bottom.vertex = bc;
	bottom.normal = Vector3(0.0f,-1.0f,0.0f);
	vertices.push_back(bottom);
	vertexCount = vertices.size();
	for (unsigned int i = 0; i <= subdivision; i++)
	{
		Vertex vertex;
		float radian = -(i * 1.0f / subdivision) * Mathf::pi * 2;
		float x = Mathf::Cos(radian);
		float z = Mathf::Sin(radian);
		vertex.vertex = bc + Vector3(x, 0.0f, z) * radius;
		vertex.normal = Vector3(0.0f, -1.0f, 0.0f);
		vertices.push_back(vertex);
		if (i < subdivision)
		{
			indices.push_back(vertexCount + i);
			indices.push_back(centerIndex);
			indices.push_back(vertexCount + i + 1);
		}
	}

	// side
	vertexCount = vertices.size();
	for (unsigned int i = 0; i <= subdivision; i++) 
	{
		float radian = (i * 1.0f / subdivision) * Mathf::pi * 2;
		float x = Mathf::Cos(radian);
		float z = Mathf::Sin(radian);

		Vertex b;
		b.vertex = bc + Vector3(x, 0.0f, z) * radius;
		b.normal = Vector3(x, 0.0f, z);
		vertices.push_back(b);

		Vertex t;
		t.vertex = tc + Vector3(x, 0.0f, z) * radius;
		t.normal = Vector3(x, 0.0f, z);
		vertices.push_back(t);

		if (i < subdivision) 
		{
			indices.push_back(vertexCount);
			indices.push_back(vertexCount + 1);
			indices.push_back(vertexCount + 3);

			indices.push_back(vertexCount + 3);
			indices.push_back(vertexCount + 2);
			indices.push_back(vertexCount);

			vertexCount = vertices.size();
		}
	}

	cylinder->vertices = vertices;
	cylinder->indices = indices;
	return cylinder;
}

Mesh* Primitive::GenCone() 
{
	float radius = 0.5f;
	float height = 0.5f;
	unsigned int subdivision = 64;
	float coneRadian = Mathf::Atan(radius / height);

	Mesh* cone = new Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// bottom
	int centerIndex = vertices.size();
	Vector3 bc = Vector3(0.0f,0.0f, 0.0f);
	Vertex bottom;
	bottom.vertex = bc;
	bottom.normal = Vector3(0.0f, -1.0f, 0.0f);
	vertices.push_back(bottom);
	int vertexCount = vertices.size();
	for (unsigned int i = 0; i <= subdivision; i++)
	{
		Vertex vertex;
		float radian = -(i * 1.0f / subdivision) * Mathf::pi * 2;
		float x = Mathf::Cos(radian);
		float z = Mathf::Sin(radian);
		vertex.vertex = bc + Vector3(x, 0.0f, z) * radius;
		vertex.normal = Vector3(0.0f, -1.0f, 0.0f);
		vertices.push_back(vertex);
		if (i < subdivision)
		{
			indices.push_back(vertexCount + i);
			indices.push_back(centerIndex);
			indices.push_back(vertexCount + i + 1);
		}
	} 

	// side
	vertexCount = vertices.size();
	for (unsigned int i = 0; i <= subdivision; i++)
	{
		float radian = (i * 1.0f / subdivision) * Mathf::pi * 2;
		float x = Mathf::Cos(radian);
		float z = Mathf::Sin(radian);

		Vertex b;
		b.vertex = bc + Vector3(x, 0.0f, z) * radius;
		b.normal = Vector3(x, 0.0f, z) * Mathf::Cos(coneRadian) + Vector3(0.0f, 1.0f, 0.0f) * Mathf::Sin(coneRadian);
		vertices.push_back(b);

		Vertex t;
		t.vertex = Vector3(0.0f,height,0.0f);
		t.normal = b.normal;
		vertices.push_back(t);

		if (i < subdivision)
		{
			indices.push_back(vertexCount);
			indices.push_back(vertexCount + 1);
			indices.push_back(vertexCount + 3);

			indices.push_back(vertexCount + 3);
			indices.push_back(vertexCount + 2);
			indices.push_back(vertexCount);

			vertexCount = vertices.size();
		}
	}

	cone->vertices = vertices;
	cone->indices = indices;
	return cone;
}

Mesh* Primitive::GenSphere() 
{
	float radius = 0.5f;
	unsigned int subdivision = 64;
	unsigned int vSubdivision = subdivision / 2;
	float perRadian = (1.0f / subdivision) * Mathf::pi * 2;

	Mesh* sphere = new Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int vertexCount = 0;
	for (unsigned int horizontal = 0; horizontal <= subdivision; horizontal++)
	{                             
		float xozRadian = horizontal * perRadian;
		float x = Mathf::Cos(xozRadian);
		float z = Mathf::Sin(xozRadian);
		Vector3 xoz = Vector3(x,0.0f,z);
		vertexCount = vertices.size();
		for (unsigned int vertical = 0; vertical <= vSubdivision; vertical++)
		{
			float vRadian = vertical * perRadian - Mathf::pi * 0.5f;
			float vx = Mathf::Cos(vRadian);
			float vy = Mathf::Sin(vRadian);

			Vertex vertex;
			Vector3 pos = xoz * vx + Vector3(0.0f, 1.0f, 0.0f) * vy;
			vertex.vertex = pos * radius;
			vertex.normal = pos;
			vertices.push_back(vertex);
			if (vertical < vSubdivision && horizontal < subdivision) 
			{
				indices.push_back(vertexCount + vertical);
				indices.push_back(vertexCount + vertical + 1);
				indices.push_back(vertexCount + vertical + 1 + vSubdivision);

				indices.push_back(vertexCount + vertical + 1 + vSubdivision);
				indices.push_back(vertexCount + vertical + vSubdivision);
				indices.push_back(vertexCount + vertical);
			}
		}
	}

	sphere->vertices = vertices;
	sphere->indices = indices;
	return sphere;
}

Mesh* Primitive::GenBand(float bRadius,float sRadius, unsigned int bSubdivision, unsigned int sSubdivision)
{
	float biggerBandRadian = (1.0f / bSubdivision) * Mathf::pi * 2;
	float samllerBandRadian = (1.0f / sSubdivision) * Mathf::pi * 2;

	Mesh* band = new Mesh();
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	int vertexCount = 0;
	for (unsigned int i = 0; i <= bSubdivision; i++)
	{
		float radian = biggerBandRadian * i;
		float x = Mathf::Cos(radian);
		float z = Mathf::Sin(radian);
		Vector3 dir = Vector3::Normalize(Vector3(x, 0.0f, z));
		Vector3 origin = dir * bRadius;

		vertexCount = vertices.size();
		for (unsigned int bIndex = 0; bIndex <= sSubdivision; bIndex++)
		{
			float bRadian = samllerBandRadian * bIndex;
			float bX = Mathf::Cos(bRadian);
			float bY = Mathf::Sin(bRadian);

			Vertex vertex;
			vertex.vertex = origin + dir * bX * sRadius + Vector3(0.0f, bY, 0.0f) * sRadius;
			vertex.normal = Vector3::Normalize(vertex.vertex - origin);
			vertices.push_back(vertex);

			if (bIndex < sSubdivision && i < bSubdivision)
			{
				indices.push_back(vertexCount + bIndex);
				indices.push_back(vertexCount + bIndex + 1);
				indices.push_back(vertexCount + bIndex + 2 + sSubdivision);

				indices.push_back(vertexCount + bIndex + 2 + sSubdivision);
				indices.push_back(vertexCount + bIndex + 1 + sSubdivision);
				indices.push_back(vertexCount + bIndex);
			}
		}
	}

	band->vertices = vertices;
	band->indices = indices;
	return band;
}

Mesh* Primitive::GenMobiusband() 
{
	unsigned int outterSubdivision = 128;
	float outterRadius = 0.5f;
	float outterPerRadian = (1.0 / outterSubdivision) * Mathf::pi * 2;

	unsigned int innerSubdivision = 4;
	unsigned int meshSubdivision = 32;
	float innerRadius = 0.15f;
	float innerPerRadian = (1.0 / innerSubdivision) * Mathf::pi * 2;

	float rotateRadian = Mathf::pi / outterSubdivision;
	int vertexCount = 0;

	Mesh* mobiusband = new Mesh();
	// mobiusband->mode = Mesh::Lines;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int outterIndex = 0; outterIndex <= outterSubdivision; outterIndex++)
	{
		float outterRadian = outterIndex * outterPerRadian;
		float outX = Mathf::Cos(outterRadian);
		float outZ = Mathf::Sin(outterRadian);
		Vector3 dir = Vector3(outX, 0.0f, outZ);
		Vector3 origin = dir * outterRadius;
		vertexCount = vertices.size();
		for (unsigned int innerIndex = 0; innerIndex <= innerSubdivision; innerIndex++)
		{
			// vertexCount = vertices.size();
			float innerRadian = innerPerRadian * innerIndex + rotateRadian * outterIndex;
			float innerX = Mathf::Cos(innerRadian);
			float innerY = Mathf::Sin(innerRadian);
			Vertex vertex;
			vertex.vertex = origin + dir * innerX * innerRadius + Vector3(0.0f,innerY,0.0f) * innerRadius;
			vertex.normal = Vector3::Normalize(vertex.vertex - origin);
			vertex.texcoord = Vector2(outterIndex/outterSubdivision,1.0f);
			vertices.push_back(vertex);
			if (meshSubdivision > 0 && innerIndex < innerSubdivision )
			{
				if (outterIndex < outterSubdivision)
				{
					indices.push_back(vertexCount);
					indices.push_back(vertexCount + 1);
					indices.push_back(vertexCount + 2 + innerSubdivision + meshSubdivision * innerSubdivision);

					indices.push_back(vertexCount + 2 + innerSubdivision + meshSubdivision * innerSubdivision);
					indices.push_back(vertexCount + 1 + innerSubdivision + meshSubdivision * innerSubdivision);
					indices.push_back(vertexCount);
				}

				float nextInnerRadian = innerPerRadian * (innerIndex + 1) + rotateRadian * outterIndex;
				float nextInnerX = Mathf::Cos(nextInnerRadian);
				float nextInnerY = Mathf::Sin(nextInnerRadian);
				Vector3 nextVertexPos = origin + dir * nextInnerX * innerRadius + Vector3(0.0f, nextInnerY, 0.0f) * innerRadius;
				Vector3 offset = nextVertexPos - vertex.vertex;
				Vector3 perOffset = offset / meshSubdivision;
				for (unsigned int meshIndex = 1; meshIndex <= meshSubdivision; meshIndex++) 
				{
					Vertex divisionVertex;
					divisionVertex.vertex = vertex.vertex + perOffset * meshIndex;
					divisionVertex.normal = vertex.normal;
					// vertex.texcoord = Vector2(outterIndex / outterSubdivision, 1.0f);
					vertices.push_back(divisionVertex);
					if (outterIndex < outterSubdivision) 
					{
						indices.push_back(vertexCount + meshIndex);
						indices.push_back(vertexCount + meshIndex + 1);
						indices.push_back(vertexCount + meshIndex + 2 + innerSubdivision + meshSubdivision * innerSubdivision);

						indices.push_back(vertexCount + meshIndex + 2 + innerSubdivision + meshSubdivision * innerSubdivision);
						indices.push_back(vertexCount + meshIndex + 1 + innerSubdivision + meshSubdivision * innerSubdivision);
						indices.push_back(vertexCount + meshIndex);
					}
				}
				vertexCount = vertices.size();
			}
			else if(meshSubdivision == 0)
			{
				if (innerIndex < innerSubdivision && outterIndex < outterSubdivision)
				{
					indices.push_back(vertexCount + innerIndex);
					indices.push_back(vertexCount + innerIndex + 1);
					indices.push_back(vertexCount + innerIndex + 2 + innerSubdivision);

					indices.push_back(vertexCount + innerIndex + 2 + innerSubdivision);
					indices.push_back(vertexCount + innerIndex + 1 + innerSubdivision);
					indices.push_back(vertexCount + innerIndex);
				}
			}
		}
	}

	PRINT_ERROR("mesh vertex count : %d",vertices.size());

	mobiusband->vertices = vertices;
	mobiusband->indices = indices;
	return mobiusband;
}

#pragma endregion