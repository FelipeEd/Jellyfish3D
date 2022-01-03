#include <jellyfish/Jellyfish3D.hpp>

Material::Material()
{
    m_color = glm::vec4(0.4f, 0.2f, 0.4f, 1.0f);
    m_texDiffuse = createTexture("resources/whitepixel.png");
}

Material::Material(const char *textureFile)
{
    m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_texDiffuse = createTexture(textureFile);
}

void Material::setUniforms(Shader &shader)
{

    glBindTexture(GL_TEXTURE_2D, m_texDiffuse);

    shader.setVec4("uColor", m_color);
}