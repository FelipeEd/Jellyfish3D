#include <jellyfish\Jellyfish3D.hpp>

void comp_Transform::lookAt(glm::vec3 target)
{
    speed = target;
}

glm::mat4 comp_Transform::getModelMatrix()
{
    glm::mat4 rotationM;

    if (speed == glm::vec3(0.0))
    {
        rotationM = glm::toMat4(glm::quat(rotation));
    }
    else
    {
        glm::vec3 axis = glm::cross(glm::vec3(0.0, 0.0, 1.0), speed);
        // if (axis.y < 0)
        //     axis = -axis;
        rotationM = glm::rotate(glm::mat4(1.0), glm::angle(glm::vec3(0.0, 0.0, 1.0), speed), axis);
    }

    return glm::translate(glm::mat4(1.0f), position) * rotationM * glm::scale(glm::mat4(1.0f), scale);
}
