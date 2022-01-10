#include <jellyfish/Jellyfish3D.hpp>

Light::Light(std::string name, glm::vec3 color, glm::vec3 pos) : Object(name, 1, 0)
{
    m_color = color;
    this->m_transform.setPosition(pos);
    this->m_transform.setScale(0.2);
}