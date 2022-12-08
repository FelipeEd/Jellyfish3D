#include "Light.hpp"

Light::Light(std::string name, glm::vec3 color, glm::vec3 pos) : Object(name, 1, 0)
{
    m_color = color;
    this->transform.position = pos;
    this->transform.scale = glm::vec3(0.2);
}