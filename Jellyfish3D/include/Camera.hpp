#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Timer.hpp>
#include <Components.hpp>
#include <KeyStates.hpp>

struct GLFWwindow;

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

class Camera
{
private:
    static constexpr float DEFAULT_FOV = 60.0f;
    static constexpr float DEFAULT_NEAR_PLANE = 0.1f;
    static constexpr float DEFAULT_FAR_PLANE = 300.0f;

    Timer m_rotatingCooldown = Timer(10);
    bool isRotating = false;
    double m_lastMouseX = 0.0;
    double m_lastMouseY = 0.0;
    bool m_firstMouse = true;
    GLFWwindow* m_window = nullptr;

    float m_FOV = DEFAULT_FOV;
    float m_nearPlane = DEFAULT_NEAR_PLANE;
    float m_farPlane = DEFAULT_FAR_PLANE;
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    comp_Transform transform;

    Camera(){};
    ~Camera(){};

    void setWindow(GLFWwindow* window) { m_window = window; }
    void pointTo(glm::vec3 pos);
    void reactToInput(KeyStates input);
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
};