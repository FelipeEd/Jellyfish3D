#include <jellyfish/Jellyfish3D.hpp>

Material::Material()
{

    useNormalmap = false;
    m_color = glm::vec4(0.4f, 0.2f, 0.4f, 1.0f);
    m_texAlbedo = createTexture("resources/textures/whitepixel.png");

    //m_texNormal = m_texAlbedo;
    // from 0 to 1
    m_texMetallic = m_texAlbedo;
    m_texRoughness = m_texAlbedo;
    m_texAo = m_texAlbedo;
}

Material::Material(const std::string &textureFile, const std::string &size)
{
    useNormalmap = false;
    m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_texAlbedo = createTexture(textureFile + "_diff" + size + ".png");
    m_texNormal = createTexture(textureFile + "_nor_gl" + size + ".png");
    m_texMetallic = createTexture(textureFile + "_arm" + size + ".png");
    m_texRoughness = createTexture(textureFile + "_rough" + size + ".png");
    m_texAo = createTexture(textureFile + "_ao" + size + ".png");
}

void Material::setUniforms(Shader &shader)
{

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texAlbedo);

    if (pbr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texNormal);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_texMetallic);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_texRoughness);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, m_texAo);
        shader.setBool("uUseNormalmap", useNormalmap);
    }
    shader.setVec4("uColor", m_color);
}