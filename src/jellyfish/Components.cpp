#include <jellyfish\Jellyfish3D.hpp>

void comp_Transform::lookAt(glm::vec3 target)
{
    rotation = glm::eulerAngles(glm::quat(target));
}

glm::mat4 comp_Transform::getModelMatrix()
{
    glm::mat4 rotationM = glm::toMat4(glm::quat(rotation));
    return glm::translate(glm::mat4(1.0f), position) * rotationM * glm::scale(glm::mat4(1.0f), scale);
}