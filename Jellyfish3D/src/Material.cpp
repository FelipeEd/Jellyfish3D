#include "Material.hpp"

#include "AuxFunctions.hpp"

Material::Material()
{

    useNormalmap = false;
    m_color = glm::vec4(0.4f, 0.2f, 0.4f, 1.0f);
    m_texAlbedo = createTexture("resources/textures/whitepixel.png");

    m_texNormal = m_texAlbedo;
    // from 0 to 1
    m_texMetallic = createTexture("resources/textures/blackpixel.png");
    m_texRoughness = m_texMetallic;
    m_texAo = m_texAlbedo;
}

Material::Material(const std::string &textureFile, const std::string &size)
{
    useNormalmap = false;
    m_color = glm::vec4(3.0f, 1.0f, 1.0f, 1.0f);
    m_texAlbedo = createTexture(textureFile + "_diff" + size + ".png");
    m_texNormal = createTexture(textureFile + "_nor_gl" + size + ".png");
    m_texMetallic = createTexture(textureFile + "_arm" + size + ".png");
    m_texRoughness = createTexture(textureFile + "_rough" + size + ".png");
    m_texAo = createTexture(textureFile + "_ao" + size + ".png");
}

void Material::deleteTextures()
{
    printf("Destroing Textures\n");
    glDeleteTextures(1, &m_texAlbedo);
    glDeleteTextures(1, &m_texNormal);
    glDeleteTextures(1, &m_texMetallic);
    glDeleteTextures(1, &m_texRoughness);
    glDeleteTextures(1, &m_texAo);
}

void Material::setUniforms(Shader &shader)
{

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texAlbedo);
    shader.setInt("uTexAlbedo", 0);

    if (pbr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texNormal);
        shader.setInt("uTexNormalMap", 1);

        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, m_texMetallic);
        shader.setInt("uTexMetallic", 2);

        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, m_texRoughness);
        shader.setInt("uTexRoughness", 3);

        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, m_texAo);
        shader.setInt("uTexAo", 4);

        shader.setBool("uUseNormalmap", useNormalmap);
    }
    shader.setVec4("uColor", m_color);
}