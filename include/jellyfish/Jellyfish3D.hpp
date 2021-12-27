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

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
};

class Shader;
class Mesh;
class Material;
class Resources;

// Useful default stuff
extern Resources *assets;

// Classe basica para compilar os shaders do openGL
class Shader
{
private:
    // the program ID
    unsigned int id;

public:
    // constructor will read and build the shader
    Shader(){};
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

class Mesh
{
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    unsigned int m_nvertex;
    unsigned int m_nindices;

    std::vector<Vertex> m_vertexData;
    std::vector<unsigned int> m_vetexIndex;

public:
    Mesh(); // Cube place holder
    ~Mesh(){};

    void genBuffer();
    void bindBuffer();

    unsigned int getNVertex();
    unsigned int getNIndices();
};

class Material
{
private:
    unsigned int m_tex_diffuse; // ! Not implemented !
    glm::vec4 m_color;

public:
    Material(); // Flat color
    ~Material(){};

    void setUniforms(Shader &shader);
};

// A class that stores all the Meshes and Materials that the application will use
// The "0" position is defined to have the default objects
class Resources
{
public:
    std::vector<Mesh> meshes;
    std::vector<Material> materials;

    Resources();
    ~Resources(){};
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

class comp_UserControl
{
};

class Object
{
private:
    comp_Transform m_transform;
    unsigned int m_mesh;
    unsigned int m_material;

public:
    Object();
    ~Object(){};

    unsigned int getMeshId();
    unsigned int getMaterialId();
};

class Camera
{
private:
    comp_Transform m_transform;

public:
    Camera();
    ~Camera(){};
};

class Renderer
{
private:
public:
    Shader m_shader;
    Renderer();
    ~Renderer(){};

    void draw(Object obj); // Later it will be a scene
};

/*
class Scene
{
private:
    Camera cam1; // Must have 3 cams later on
    std::vector<Object> m_objects;

public:
    Scene();
    ~Scene(){};
};
*/