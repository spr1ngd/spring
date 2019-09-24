#include "camera.h"
#include "screen.h"
#include "graphic.h"

using namespace spring;

Camera* Camera::main;

Camera::Camera() 
{
	this->transform = new Transform();
	this->center = Vector3(0.0f,0.0f,-1.0f);
	this->direction = Vector3(0.0f,1.0f,0.0f);
	this->background = Color(123,134,125,255);
	Camera::main = this;
}

void Camera::LookAt(const Node* target) 
{

}

void Camera::LookAt(const Vector3* target) 
{

}

void Camera::Render() 
{
	glm::mat4 view = glm::lookAt(
		glm::vec3(this->transform->position.x,this->transform->position.y,this->transform->position.z), 
		glm::vec3(this->center.x,this->center.y,this->center.z), // replace this by transform.back
		glm::vec3(this->direction.x,this->direction.y,this->direction.z)); // replace this by transform.up
	// note : perspective fov parameter is radian.
	glm::mat4 projection = glm::perspective(glm::radians(this->fov), float(Screen::width) / float(Screen::height),this->nearClip, this->farClip);
	Graphic::VIEW = view;
	Graphic::PROJECTION = projection;

	switch (this->clearFlag)
	{
	case Camera::ClearFlag::Skybox:
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		break;
	case Camera::ClearFlag::SolidColor:
		glClearColor(
			this->background.r / 255.0f,
			this->background.g / 255.0f,
			this->background.b / 255.0f,
			1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		break;
	case Camera::ClearFlag::Depth:
		glClear(GL_DEPTH_BUFFER_BIT);
		break;
	case Camera::ClearFlag::None:
		break;
	default:
		break;
	}
}