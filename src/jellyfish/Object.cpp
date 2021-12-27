#include <jellyfish/Jellyfish3D.hpp>

Object::Object()
{
    m_mesh = 0;
    m_material = 0;
}

unsigned int Object::getMeshId() { return m_mesh; };
unsigned int Object::getMaterialId() { return m_material; };