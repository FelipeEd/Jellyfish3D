#pragma once

#include <map>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

struct comp_Transform
{

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    comp_Transform() {}

    void lookAt(glm::vec3 target);

    glm::mat4 getModelMatrix();
};

struct comp_UserControl
{

    double m_mouseX;
    double m_mouseY;

    double m_oldMouseX;
    double m_oldMouseY;

    std::map<std::string, bool> m_inputs;

    comp_UserControl();
    ~comp_UserControl(){};

    void observeInputs(GLFWwindow *window);
    void resetState();
    void printInputs();
};