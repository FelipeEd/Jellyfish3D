#include "Object.hpp"

Object::Object()
{
    m_mesh = 0;
    m_material = 0;
}

Object::Object(const std::string &name, unsigned int mesh, unsigned int material)
{
    m_name = name;
    m_mesh = mesh;
    m_material = material;
}

void Object::reactToInput(GLFWwindow *window, KeyStates input)
{

    float leaderSpeed = 0.2;
    float turnSpeed = 0.1;

    if (input.keys["shipleft"])
    {
        transform.rotation += glm::vec3(0.0f, turnSpeed, 0.0f);
    }
    if (input.keys["shipright"])
    {
        transform.rotation += -glm::vec3(0.0f, turnSpeed, 0.0f);
    }
    if (input.keys["shipup"])
    {
        transform.rotation += -glm::vec3(turnSpeed, 0.00f, 0.0f);
    }
    if (input.keys["shipdown"])
    {
        transform.rotation += +glm::vec3(turnSpeed, 0.00f, 0.0f);
    }

    transform.position += glm::vec3(leaderSpeed * glm::mat4(glm::quat(transform.rotation)) * glm::vec4(0.0, 0.0, 1.0, 1.0)); // glm::vec3(leaderSpeed * glm::eulerAngleXY(transform.rotation.x, transform.rotation.y) * glm::vec4(0.0, 0.0, 1.0, 1.0));
}

glm::mat4 Object::getModelMatrix() { return transform.getModelMatrix(); }
unsigned int Object::getMeshId() { return m_mesh; }
unsigned int Object::getMaterialId() { return m_material; }
std::string Object::getName() { return m_name; }