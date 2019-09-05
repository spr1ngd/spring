#include "Camera.h"

using namespace spring;

Camera::Camera() 
{
	this->transform = new Transform();
	this->center = new Vector3(0.0f,0.0f,-1.0f);
	this->direction = new Vector3(0.0f,1.0f,0.0f);
}

void Camera::LookAt(const Node* target) 
{

}

void Camera::LookAt(const Vector3* target) 
{

}

void Camera::Render( Model* model ) 
{
	glm::mat4 view = glm::lookAt(
		glm::vec3(this->transform->position.x,this->transform->position.y,this->transform->position.z), 
		glm::vec3(this->center->x,this->center->y,this->center->z), 
		glm::vec3(this->direction->x,this->direction->y,this->direction->z));
	glm::mat4 projection = glm::perspective(this->fov, 800.0f / 600.0f,this->nearClip, this->farClip);
	model->Render(view, projection);
}