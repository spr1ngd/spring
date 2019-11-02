#include "camera.h"
#include "screen.h"
#include "graphic.h"

using namespace spring;

std::vector<Camera*> Camera::cameras;
Camera* Camera::main;

Camera::Camera() 
{
	this->direction = Vector3(0.0f,1.0f,0.0f);
	this->background = Color(123,134,125,255);
	CachingCamera(this);
}

void Camera::Destroy()
{
	for (vector<Camera*>::iterator cam = cameras.begin(); cam != cameras.end();cam++) 
	{
		if ( *cam == this)
		{
			cameras.erase(cam);
			return;
		}
	}
}

void Camera::LookAt(const Node* target) 
{

}

void Camera::LookAt(const Vector3* target) 
{

}

void Camera::Render() 
{
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

glm::mat4 Camera::GetViewMatrix() 
{
	Vector3 up = this->transform->up;
	glm::mat4 view = glm::lookAt(
		glm::vec3(this->transform->position.x, this->transform->position.y, this->transform->position.z),
		glm::vec3(this->center.x, this->center.y, this->center.z),
		glm::vec3(up.x, up.y, up.z));
	return view;
}

glm::mat4 Camera::GetProjectionMatrix() 
{
	// todo : modify matrix by camera's parameters.
	if (this->cameraType == Camera::Perspective) 
	{
		return glm::perspective(glm::radians(this->fov), float(Screen::width) / float(Screen::height), this->nearClip, this->farClip);
	}
	else if( this->cameraType == Camera::Orthographic )
	{
		return glm::ortho(0.0f,static_cast<float>(Screen::halfWidth),0.0f,static_cast<float>(Screen::height),-1.0f,1.0f);
	}
	else 
	{
		throw new std::invalid_argument("spring engine : camera type invalid.");
	}
}

void Camera::CachingCamera(Camera* camera) 
{
	if (cameras.size() == 0)
		Camera::main = camera;
	cameras.push_back(camera);
}