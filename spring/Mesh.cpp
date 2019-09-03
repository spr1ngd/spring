#include "Mesh.h"

using namespace spring;

Mesh::Mesh() 
{

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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(positions) * 3, &positions, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pvertices), pvertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::GenVAO( function<void()> setting )
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	/*glEnableVertexAttribArray();
	glVertexAttribPointer();*/
	if ( nullptr != setting)
		setting();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::GenEBO()
{
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, &indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, pindices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::Draw( function<void()> render )
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

	if (nullptr != render)
		render();

	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, &indices);
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
}