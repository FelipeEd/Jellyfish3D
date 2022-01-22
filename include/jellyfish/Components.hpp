#pragma once
#include <map>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

struct comp_Transform
{

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    comp_Transform() {}

    glm::mat4 getModelMatrix()
    {
        // glm::mat4 model(1.0f);
        // model = glm::translate(model, m_Position);
        // model = glm::scale(model, m_Scale);
        // model = glm::rotate(glm::rotate(glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0, 0.0, 0.0)), glm::radians(m_Rotation.y), glm::vec3(0.0, 1.0, 0.0)), glm::radians(m_Rotation.z), glm::vec3(0.0, 0.0, 1.0));
        // return model;
        glm::mat4 rotationM = glm::toMat4(glm::quat(rotation));

        return glm::translate(glm::mat4(1.0f), position) * rotationM * glm::scale(glm::mat4(1.0f), scale);
    }
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