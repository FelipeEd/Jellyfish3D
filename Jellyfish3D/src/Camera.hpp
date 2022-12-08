#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Timer.hpp"
#include "Components.hpp"
#include "KeyStates.hpp"

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

class Camera
{
private:
    Timer m_rotatingCooldown = Timer(10);
    bool isRotating = false;

    float m_FOV = 60.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 300.0f;
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    comp_Transform transform;

    Camera(){};
    ~Camera(){};

    void pointTo(glm::vec3 pos);
    void reactToInput(GLFWwindow *window, KeyStates input);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};