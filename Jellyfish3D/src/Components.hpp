#pragma once

#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glm/gtx/vector_angle.hpp> //! Talvez nao seja a função angle antiga

struct comp_Transform
{

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 speed = glm::vec3(0.0);

    comp_Transform() {}

    void lookAt(glm::vec3 target);

    glm::mat4 getModelMatrix();
};
