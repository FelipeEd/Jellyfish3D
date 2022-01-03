#include <Jellyfish/Jellyfish3D.hpp>

comp_Transform::comp_Transform()
{
    this->m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->m_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

glm::mat4 comp_Transform::getScaleMatrix() { return glm::scale(id, m_Scale); }
glm::mat4 comp_Transform::getRotateMatrix() { return glm::rotate(glm::rotate(glm::rotate(id, glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0)), glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0)), glm::radians(m_Rotation.z), glm::vec3(0.0, 0.0, 1.0)); }
glm::mat4 comp_Transform::getTranslateMatrix() { return glm::translate(id, m_Position); }

void comp_Transform::setPosition(glm::vec3 newPos) { m_Position = newPos; }
void comp_Transform::setRotation(glm::vec3 newRot) { m_Rotation = newRot; }
void comp_Transform::setScale(glm::vec3 newScale) { m_Scale = newScale; }
void comp_Transform::setScale(float newScale) { m_Scale = glm::vec3(newScale, newScale, newScale); }

glm::vec3 comp_Transform::getPosition() { return m_Position; }
glm::vec3 comp_Transform::getRotation() { return m_Rotation; }
glm::vec3 comp_Transform::getScale() { return m_Scale; }