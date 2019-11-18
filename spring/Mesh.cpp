#include "mesh.h" 
#include "console.h"

using namespace spring;

Mesh::Mesh() 
{

}

Mesh::~Mesh() 
{
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	glDeleteVertexArrays(1, &this->VAO);
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int>indices, vector<Texture> textures) 
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
}

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

// todo : remove this method to mesh renderer object
void Mesh::Draw( function<void()> render )
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	if (nullptr != render)
		render();

	auto mode = GetDrawMode(this->mode);
	glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}