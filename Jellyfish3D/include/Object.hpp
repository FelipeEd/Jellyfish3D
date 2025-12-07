#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <Components.hpp>
#include <KeyStates.hpp>

class Object
{
protected:
    unsigned int m_mesh;
    unsigned int m_material;
    std::string m_name;

public:
    bool isBoids = false; //! REMOVE THIS AAAAAAA
    comp_Transform transform;
    Object();
    Object(const std::string &name, unsigned int mesh, unsigned int material);
    ~Object(){};

    void reactToInput(GLFWwindow *window, KeyStates input);

    glm::mat4 getScaleMatrix() const;
    glm::mat4 getRotateMatrix() const;
    glm::mat4 getTranslateMatrix() const;
    glm::mat4 getModelMatrix() const;

    unsigned int getMeshId() const noexcept { return m_mesh; }
    unsigned int getMaterialId() const noexcept { return m_material; }
    const std::string& getName() const noexcept { return m_name; }

    void setMeshId(unsigned int id) { m_mesh = id; }
};