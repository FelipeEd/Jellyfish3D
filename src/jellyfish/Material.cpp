#include <jellyfish/Jellyfish3D.hpp>

Material::Material()
{
    m_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
}

void Material::setUniforms(Shader &shader)
{
    shader.setVec4("uColor", m_color);
}