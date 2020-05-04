#include "mesh.h" 
#include "console.h"
#include "matrix4x4.h"

using namespace spring;

Mesh::Mesh() 
{

}
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int>indices) 
{
	this->vertices = vertices;
	this->indices = indices;
}
Mesh::~Mesh() 
{
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	glDeleteVertexArrays(1, &this->VAO);
}

unsigned int Mesh::GetSubMeshCount() 
{
	return this->subMeshes.size();
}
vector<Mesh*> Mesh::GetAllSubMeshes()
{
	return this->subMeshes;
}
Mesh& Mesh::GetSubMesh(unsigned int subMeshIndex) 
{
	return *this->subMeshes[subMeshIndex];
}
void Mesh::SetSubMesh(Mesh* subMesh) 
{
	this->subMeshes.push_back(subMesh);
}

void Mesh::RTS(Matrix4x4 rts) 
{
	for (unsigned int i = 0; i < this->vertices.size(); i++) 
	{
		Vector3 vertex = this->vertices[i].vertex;
		this->vertices[i].vertex = rts * vertex;
	}
}

void Mesh::Combine(Mesh& mesh)
{
	unsigned int verticesCount = this->vertices.size();
	this->vertices.insert(this->vertices.end(), mesh.vertices.begin(), mesh.vertices.end());
	for (auto index : mesh.indices)
		this->indices.push_back(verticesCount + index);
}

void Mesh::Clear() 
{
	this->vertices.clear();
	this->indices.clear();
}

#pragma region renderer core

void Mesh::Init(function<void()> setting) 
{
	if (this->initialized)
		return;
	this->GenVBO();
	this->GenVAO(setting);
	this->GenEBO();
	this->initialized = true;
}
void Mesh::GenVBO()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], this->GetDrawUsage());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Mesh::GenVAO( function<void()> setting )
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	if ( nullptr != setting)
		setting();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Mesh::GenEBO()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], this->GetDrawUsage());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::Draw( function<void()> render )
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	if (nullptr != render)
		render();
	auto mode = GetDrawMode(this->mode);
	glDrawElements(mode, (GLsizei)indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}
void Mesh::DrawInstanced(unsigned int instancedCount,function<void()> render) 
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	if (nullptr != render)
		render();
	auto mode = GetDrawMode(this->mode);
	glDrawElementsInstanced(mode, (GLsizei)indices.size(), GL_UNSIGNED_INT,0, instancedCount);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

#pragma endregion