#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stbi/stb_image.h>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <chrono>
#include <thread>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

class Display;
class Shader;
class Mesh;
class Material;
class Resources;
class Object;

// Useful default stuff
extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern Resources *assets;

void initOpengl();
std::vector<Vertex> loadOBJ(const char *file_name);
unsigned int createTexture(const char *textureName);

// Should be used when limiting function calls by framerate
class Clock
{
private:
    double prevTime = 0.0;
    double crntTime = 0.0;
    double timeDiff;
    double tickSpeed = 1 / 30; // ! 30 times per second !

public:
    Clock();
    ~Clock(){};

    bool tick();
};

// Must be used inside a function that runs inside the clock
class Timer
{
private:
    unsigned int m_alarm;
    unsigned int m_framesLeft;

public:
    // After this many frames it will wake up
    Timer(unsigned int alarm);
    bool isUp();
    void tick();
    void reset();
};

// For now handles opengl init stuff
class Display
{
private:
    GLFWwindow *m_window;
    void processInput(GLFWwindow *window);

public:
    GLFWwindow *getWindow() { return m_window; }

    Display();
    ~Display() { glfwTerminate(); }
};

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
    void use();
    // Utility functions to set values to uniforms in the shader program
    void setBool(const std::string &uniformName, bool value) const;
    void setInt(const std::string &uniformName, int value) const;
    void setFloat(const std::string &uniformName, float value) const;
    void setVec2(const std::string &uniformName, glm::vec2 value) const;
    void setVec4(const std::string &uniformName, glm::vec4 value) const;
    void setMat4(const std::string &uniformName, glm::mat4 value) const;
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
    Mesh(const char *objName);
    ~Mesh(){};

    void genBuffer();
    void bindBuffer();

    unsigned int getNVertex();
    unsigned int getNIndices();
};

class Material
{
private:
    unsigned int m_texDiffuse;

    glm::vec4 m_color;

public:
    Material(); // Flat color
    Material(const char *textureFile);
    ~Material(){};

    void setColor(glm::vec4 color) { m_color = color; }
    void setUniforms(Shader &shader);
};

// A class that stores all the Meshes and Materials that the application will use
// The "0" position is defined to have the default objects
class Resources
{
public:
    std::vector<Mesh> meshes;
    std::vector<Material> materials;

    // Loads a Mesh from a obj file into the resources
    void loadMesh(const char *fileName);

    // Loads a texture and sets the material
    void loadMaterial(const char *fileName); //TODO: More atributes to the material

    Resources();
    ~Resources(){};
};

class comp_Transform
{
private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    glm::mat4 id = glm::mat4(1.0f);

public:
    comp_Transform();

    void setPosition(glm::vec3 newPos);
    void setRotation(glm::vec3 newRot);
    void setScale(glm::vec3 newScale);
    void setScale(float newScale);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    glm::mat4 getScaleMatrix();
    glm::mat4 getRotateMatrix();
    glm::mat4 getTranslateMatrix();
};

class comp_UserControl
{
private:
public:
    double m_mouseX;
    double m_mouseY;

    double m_oldMouseX;
    double m_oldMouseY;

    std::map<std::string, bool> m_inputs;

    comp_UserControl();
    ~comp_UserControl(){};

    void observeInputs(GLFWwindow *window);
    void resetState();
    void printInputs();
};

class Object
{
private:
    comp_UserControl m_userControl;
    unsigned int m_mesh;
    unsigned int m_material;
    std::string m_name;

public:
    comp_Transform m_transform;
    Object();
    Object(std::string name, unsigned int mesh, unsigned int material);
    ~Object(){};

    void reactToInput(GLFWwindow *window);

    glm::mat4 getScaleMatrix();
    glm::mat4 getRotateMatrix();
    glm::mat4 getTranslateMatrix();

    unsigned int getMeshId();
    unsigned int getMaterialId();
    std::string getName();

    void setMeshId(unsigned int id) { m_mesh = id; }
};

// Light types
enum ltype
{
    directional,
    point
};

class Light
{
private:
    ltype type;

public:
};

class Camera
{
private:
    comp_Transform m_transform;
    comp_UserControl m_userControl;

    Timer m_rotatingCooldown = Timer(10);
    bool isRotating = false;

    float m_FOV = 60.0f;
    float m_nearPlane = 0.1f;
    float m_farPlane = 1000.0f;
    glm::vec3 m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    Camera(){};
    ~Camera(){};

    void reactToInput(GLFWwindow *window);
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};

class Scene
{
private:
    Camera m_cam1; // Must have 3 cams later on
public:
    std::vector<Object> m_object; // TODO: Use a better container, such as a dict

    Scene();
    ~Scene(){};

    // Create a object with especified mesh and material
    void addObject(std::string name, unsigned int meshID, unsigned int materialId);
    // Adds a object onto the scene objects list
    void addObject(Object obj);

    Camera *getActiveCam() { return &m_cam1; };

    void setPosition(std::string name, glm::vec3 newPos);
    void setRotation(std::string name, glm::vec3 newPos);
    void setScale(std::string name, glm::vec3 newPos);
    void setScale(std::string name, float newPos);

    glm::vec3 getPosition(std::string name);
    glm::vec3 getRotation(std::string name);
    glm::vec3 getScale(std::string name);
};

class Renderer
{
private:
public:
    Shader m_shader;
    Renderer();
    ~Renderer(){};

    void draw(Scene);
};
