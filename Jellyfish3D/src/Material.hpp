#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Shader.hpp"

extern bool pbr;

class Material
{
private:
public:
    unsigned int m_texAlbedo;

    // TODO    change to textures
    unsigned int m_texMetallic;
    unsigned int m_texNormal;
    unsigned int m_texRoughness;
    unsigned int m_texAo;
    // Load Ao Roughness and Metallic on one texture
    unsigned int m_texARM;

    glm::vec4 m_color;

    bool useNormalmap;

public:
    Material(); // Flat color
    Material(const std::string &textureFile, const std::string &size);
    ~Material(){};

    void deleteTextures();

    void setColor(glm::vec4 color) { m_color = color; }
    void setUniforms(Shader &shader);
};
