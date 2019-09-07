#include "Mesh.h"
#define USE_UNION 

using namespace spring;

Mesh::Mesh() 
{

}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int>indices, vector<Texture> textures) 
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

void Mesh::Init(function<void()> setting) 
{
	this->GenVBO();
	this->GenVAO(setting);
	this->GenEBO();
}

void Mesh::GenVBO()
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// vector<Vector3>
	// vector<Vertex>
	// todo : fixed 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw( function<void()> render )
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	if (nullptr != render)
		render();

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}