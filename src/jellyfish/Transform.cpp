#include <Jellyfish/Jellyfish3D.hpp>

comp_Transform::comp_Transform()
{
    m_Position = {0.0f, 0.0f, 0.0f};
    m_Rotation = {0.0f, 0.0f, 0.0f};
    m_Scale = {1.0f, 1.0f, 1.0f};
}

void comp_Transform::setPosition(glm::vec3 newPos) { m_Position = newPos; };
void comp_Transform::setRotation(glm::vec3 newRot) { m_Rotation = newRot; };
void comp_Transform::setScale(glm::vec3 newScale) { m_Scale = newScale; };

glm::vec3 comp_Transform::getPosition() { return m_Position; };
glm::vec3 comp_Transform::getRotation() { return m_Rotation; };
glm::vec3 comp_Transform::getScale() { return m_Scale; };

glm::mat4 comp_Transform::getTransformMatrix()
{
    // Identity
    glm::mat4 transform = glm::mat4(1.0f);
    // euler angles for each x y z axis (possible gimble lock)
    transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0));
    transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0));
    transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0.0, 0.0, 1.0));

    transform = glm::scale(transform, m_Scale);
    transform = glm::translate(transform, m_Position);

    return transform;
}
/*
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
*/