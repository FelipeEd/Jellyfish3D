#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stbi/stb_image.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <chrono>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

extern Shader shaderProgram;

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

// Classe basica para compilar os shaders do openGL
class Shader
{
private:
    // the program ID
    unsigned int id;

public:
    // constructor will read and build the shader
    Shader();
    Shader(const char *vertexPath, const char *fragmentPath);
    // function to use/activate this shader
    void use();
    // utility functions to set values to uniforms in the shader program
    void setBool(const std::string &uniformName, bool value) const;
    void setInt(const std::string &uniformName, int value) const;
    void setFloat(const std::string &uniformName, float value) const;
    void setVec2(const std::string &uniformName, glm::vec2 value) const;
    void setVec4(const std::string &uniformName, glm::vec4 value) const;
    void Delete() const;
};

class comp_Transform
{
private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

public:
    comp_Transform();

    void setPosition(glm::vec3 newPos);
    void setRotation(glm::vec3 newRot);
    void setScale(glm::vec3 newScale);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    glm::mat4 getTransformMatrix();
};

class comp_Camera
{
};

class comp_UserControl
{
};

class comp_Mesh
{
    std::vector<Vertex> m_vertexData;
};

class comp_Material
{
    unsigned int tex_diffuse;
    Shader m_shader;
};

class Object
{
private:
    comp_Transform m_transform;
    comp_Camera m_camera;
    comp_Mesh m_mesh;
    comp_Material m_material;

public:
    Object(){};
    ~Object();
};