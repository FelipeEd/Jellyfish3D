#include <jellyfish/Jellyfish3D.hpp>

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

glm::mat4 Object::getModelMatrix() { return transform.getModelMatrix(); }

void Object::reactToInput(GLFWwindow *window, KeyStates input)
{

    if (input.keys["bleft"])
    {
        transform.position += glm::vec3(-0.01f, 0.0f, 0.0f);
    }
    if (input.keys["bright"])
    {
        transform.position += glm::vec3(0.01f, 0.0f, 0.0f);
    }
    if (input.keys["bup"])
    {
        transform.position += glm::vec3(0.0f, 0.01f, 0.0f);
    }
    if (input.keys["bdown"])
    {
        transform.position += glm::vec3(0.00f, -0.01f, 0.0f);
    }
}

unsigned int Object::getMeshId() { return m_mesh; }
unsigned int Object::getMaterialId() { return m_material; }
std::string Object::getName() { return m_name; }