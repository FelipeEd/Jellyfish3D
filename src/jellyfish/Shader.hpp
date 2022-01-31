#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <glm\glm.hpp>

// Classe basica para compilar os shaders do openGL
class Shader
{
private:
    // the program ID
    unsigned int id;

public:
    // Constructor will read and build the shader
    Shader(){};
    Shader(const char *vertexPath, const char *fragmentPath);
    // Function to use/activate this shader
    void use() const;
    // Utility functions to set values to uniforms in the shader program
    void setBool(const std::string &uniformName, bool value) const;
    void setInt(const std::string &uniformName, int value) const;
    void setFloat(const std::string &uniformName, float value) const;
    void setVec2(const std::string &uniformName, glm::vec2 value) const;
    void setVec3(const std::string &uniformName, glm::vec3 value) const;
    void setVec4(const std::string &uniformName, glm::vec4 value) const;
    void setMat4(const std::string &uniformName, glm::mat4 value) const;
    void Delete() const;
};