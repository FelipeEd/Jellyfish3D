#include <jellyfish/Jellyfish3D.hpp>

Object::Object()
{
    m_mesh = 0;
    m_material = 0;
}

glm::mat4 Object::getTransformMatrix() { return m_transform.getTransformMatrix(); }

void Object::reactToInput(GLFWwindow *window)
{

    m_userControl.observeInputs(window);

    if (m_userControl.m_inputs["bleft"])
    {
        m_transform.setPosition(m_transform.getPosition() + glm::vec3(-0.01f, 0.0f, 0.0f));
    }
    if (m_userControl.m_inputs["bright"])
    {
        m_transform.setPosition(m_transform.getPosition() + glm::vec3(0.01f, 0.0f, 0.0f));
    }
    if (m_userControl.m_inputs["bup"])
    {
        m_transform.setPosition(m_transform.getPosition() + glm::vec3(0.0f, 0.01f, 0.0f));
    }
    if (m_userControl.m_inputs["bdown"])
    {
        m_transform.setPosition(m_transform.getPosition() + glm::vec3(0.00f, -0.01f, 0.0f));
    }

    m_userControl.resetState();
}

unsigned int Object::getMeshId() { return m_mesh; }
unsigned int Object::getMaterialId() { return m_material; }