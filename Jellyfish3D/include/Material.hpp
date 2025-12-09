#pragma once

#include <string>

#include <glm/glm.hpp>

#include <Shader.hpp>

enum class RenderMode;

class Material
{
private:
public:
    unsigned int m_texAlbedo = 0;

    // TODO    change to textures
    unsigned int m_texMetallic = 0;
    unsigned int m_texNormal = 0;
    unsigned int m_texRoughness = 0;
    unsigned int m_texAo = 0;
    // Load Ao Roughness and Metallic on one texture
    unsigned int m_texARM = 0;

    glm::vec4 m_color;

    bool useNormalmap = false;

public:
    Material(); // Flat color
    Material(const std::string &textureFile, const std::string &size);
    ~Material() { deleteTextures(); }
    
    // Move semantics
    Material(Material&& other) noexcept;
    Material& operator=(Material&& other) noexcept;
    
    // Prevent copying
    Material(const Material&) = delete;
    Material& operator=(const Material&) = delete;

    void deleteTextures();

    void setColor(glm::vec4 color) { m_color = color; }
    void setUniforms(Shader &shader, RenderMode mode);
};
