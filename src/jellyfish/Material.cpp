#include <jellyfish/Jellyfish3D.hpp>

Material::Material()
{
    m_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
}

void Material::setUniforms(Shader &shader, Object obj)
{
    shader.setMat4("uTransform", obj.getTransformMatrix());
    shader.setVec4("uColor", m_color);
}