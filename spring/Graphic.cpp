#include "graphic.h"
#include "screen.h"

using namespace spring;

glm::mat4 Graphic::VIEW = glm::mat4(1.0f);
glm::mat4 Graphic::PERSPECTIVE_PROJECTION = glm::mat4(1.0f);
glm::mat4 Graphic::ORTHO_PROJECTION = glm::ortho(0.0f, static_cast<float>(Screen::width),0.0f, static_cast<float>(Screen::height), -100.0f, 1000.0f);